/**

DESCRIPTIONS NEEDED

**/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <curses.h>
#include <ncurses.h>
#include <menu.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

using namespace std;

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))


 

//PROTOTYPES
string load_file(const char * fileptr);
bool close_file(int &fd);
bool init_menu_window(MENU* menu, WINDOW* win, ITEM* current);
void run_editor(const char * fileptr);
string get_filename(const char * fileptr);
void file_to_screen(string data, WINDOW * win, int height, int width);
int show_menu_window(int menu_h, int menu_w, int menu_y, int menu_x);
string load_file(const char * fileptr){
  string filename = get_filename(fileptr);
  int fd = open(filename.c_str(), O_RDWR | O_CREAT | O_APPEND);
  if(fd < 0){
    //int errorNum = errno;
    //error window
    //return int referring to type of error
    return "";
  }
  else{
    const int BUFF_SIZE = 1024;
    char buffer[BUFF_SIZE];
    int n = 0;
    string data = "";
    while((n = read(fd, buffer, BUFF_SIZE)) > 0){
    //write?
    	for(int i = 0; i < n; i++){
		data += buffer[i];
      	}
    }
    return data;
  }
  
  
  /*do{
    bytes_read = read(fd, buffer, sizeof(buffer));
    
    for(unsigned int i=0; i<bytes_read; i++)
      data += buffer[i];

  }while(bytes_read == sizeof(buffer));
  return data;*/
  

}




bool close_file(int &fd){
  fd = close(fd);
  if(fd < 0){
    int errorNum = errno;
    printf("\nclose_file: fd: %i: Error.\n", fd);
    printf("errno: %i - %s\n\n",errorNum, strerror(errorNum));
    return false;
  }
  return true;
}


bool init_menu_window(MENU* menu, WINDOW* win, ITEM* current){
  int ch = 4;
  post_menu(menu);
  wrefresh(win);
  while(ch != KEY_F(1)){
    ch = wgetch(win);
    switch(ch){

    case KEY_DOWN:
      menu_driver(menu, REQ_DOWN_ITEM);
      break;
    case KEY_UP:
      menu_driver(menu, REQ_UP_ITEM);
      break;


    }
    current = current_item(menu);

    wrefresh(win);

  }
  unpost_menu(menu);
  wrefresh(win);
  return false;
}

void run_editor(const char *fileptr){
  WINDOW *term_win;
  WINDOW *edit_win;
  string filename = get_filename(fileptr);
  initscr();
  cbreak();
  noecho();

  int term_h, term_w;
  getmaxyx(stdscr, term_h, term_w);
  
  int menu_h = term_h/2;
  int menu_w = term_w/2;
  int menu_x = (term_w / 4), menu_y = (term_h / 4);

  int edit_x = 1, edit_y = 1;
  int edit_h = (term_h * 0.90);
  int edit_w = (term_w * 0.90);
  term_win = newwin(term_h, term_w, 0, 0);
  edit_win = derwin(term_win, edit_h, edit_w, edit_x, edit_y);

  box(edit_win, '*', '*');
  touchwin(edit_win);
  keypad(term_win, true);
  keypad(edit_win, true);

  refresh();

  mvwprintw(term_win, 0, 0, "F1: Menu");
  mvwprintw(term_win, 0, (term_w/2)-18, "CSCI 1730 Editor");
  mvwprintw(term_win, (term_h-1), 0, filename.c_str());

  file_to_screen(load_file(fileptr), edit_win, edit_h, edit_w);
  

  wrefresh(term_win);
  wrefresh(edit_win);
  int key = 1;
  while(key != KEY_UP){
    key = wgetch(edit_win);
    switch(key){
    case KEY_F(1):
      int selection = show_menu_window(menu_h, menu_w, menu_y, menu_x);
      wrefresh(term_win);
      if(selection == 0){
	 wrefresh(term_win);
         wrefresh(edit_win);	 
      }
      else if(selection == 1){

      }
      else if(selection == 2){

      }
      else if(selection == 3){

      }
      else if(selection == 4){

      }
      break;
    }
    wrefresh(term_win);
    wrefresh(edit_win);
  }

  delwin(edit_win);
  delwin(term_win);;
  endwin();
}


string get_filename(const char * fileptr){
  if (fileptr == nullptr){
    return "Untitled";
  }
  else {
    string fn = fileptr;
    return fn;
  }
}

void file_to_screen(string data, WINDOW * win, int h, int w){
  int x = 1;
  int y = 1;
  int height = h - 1;
  int width = w - 1;
  // getmaxyx(win, height, width);
  int ct = 0;
  for(int i = 0; i < data.size(); i++){
    char ch = data[i];
    /*
    if((ch == ' ' )||(ch == '\n')){
      int ct2 = 0;
      for(int j = i; j < data.size(); j++){
	if((data[j] != ' ') && (data[j] != '\n')){
	  ct2++;
	}
      }
      if(ct2 != 0){
	ct++;
      }
    }
    else{
      ct++;
    }
    bool eof = false;
    for(int i = 0; i < data.size(); i++){
    char ch = data[i];
    
    if((ch == ' ' )||(ch == '\n')){
      int ct = 0;
      for(int j = i; j < data.size(); j++){
	if((data[j] != ' ') && (data[j] != '\n')){
	  ct++;
	}
      }
      if (ct == 0){     //no other characters past last space or newline means end of text and therefore
	eof = true;     //where we start typing
      }
    }
    if(!eof){*/
      mvwprintw(win, x, y, "%c", ch);
      if(y == (width - 1) || ch == '\n'){
	x++;
	y = 1;
	//mvwprintw(win, x, y,"%c", '\n');
      }
      y++;
    
  
 
}
}


int show_menu_window(int menu_h, int menu_w, int menu_y, int menu_x){
  
  WINDOW *menu_win;
  WINDOW *menu_subwin;

  MENU *main_menu;

  ITEM **items;
  initscr();

  const char * choices[] = {"Open","Save","Save As", "Exit"};
  int n_choices = ARRAY_SIZE(choices); 

  items = (ITEM**)calloc(n_choices+1, sizeof(ITEM*));
  for(int i = 0; i < n_choices; i++){
    items[i] = new_item(choices[i], NULL);
  }
  items[n_choices] = (ITEM*)NULL;

  main_menu = new_menu((ITEM**)items);

  menu_win = newwin(menu_h, menu_w, menu_y, menu_x);
  menu_subwin = derwin(menu_win, (menu_h/2), (menu_w/2), (menu_h*0.4), (menu_w/3));
  keypad(menu_win, true);
  set_menu_win(main_menu, menu_win);
  set_menu_sub(main_menu, menu_subwin);
  set_menu_mark(main_menu, "* ");
  box(menu_win, '*', '*');
  mvwprintw(menu_win, 2, (menu_w/2)-4, "My Menu");
  refresh();

  int key = 1;
  int choice = 0;
  post_menu(main_menu);
  wrefresh(menu_win);
  while(key != KEY_F(1)){
    //ITEM *cur_item = current_item(main_menu);
    key = wgetch(menu_win);
    switch(key){

    case KEY_DOWN:
      menu_driver(main_menu, REQ_DOWN_ITEM);
      break;
    case KEY_UP:
      menu_driver(main_menu, REQ_UP_ITEM);
      break;      
    case KEY_ENTER:
      //MORE TO DO HERE
      break;

    }
    wrefresh(menu_win);

  }
  unpost_menu(main_menu);
  free_menu(main_menu);
  for(int i=0; i < n_choices; i++){
    free_item(items[i]);
  }
  delwin(menu_subwin);
  delwin(menu_win);
 
  endwin();
  refresh();

  return choice; //USER EXITS MENU (F1 Pressed)
}

void type(

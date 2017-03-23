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

string load_file(const char * fileptr){
  string filename = get_filename(fileptr);
  int fd = open(filename.c_str(), O_RDWR | O_CREAT | O_APPEND);
  if(fileptr == nullptr){
    return ""; //if program opens with no file
  }
  else if(fd < 0){
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
    //file_to_screen(data, edit_win);
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

  WINDOW *bg_win;
  WINDOW *edit_win;
  WINDOW *menu_win;
  
 
  WINDOW *menu_subwin;
  string filename = get_filename(fileptr);
  MENU *main_menu;

  ITEM **items;
  ITEM *cur_item;
  const char* choices[] = {"Open","Save","Save As", "Exit"};


  int n_choices = ARRAY_SIZE(choices);
  int term_h, term_w;
  int edit_h, edit_w;
  int menu_h, menu_w;

  initscr();
  cbreak();
  noecho();

  getmaxyx(stdscr, term_h, term_w);
  int edit_x = 1, edit_y = 1;
  menu_h = term_h/2;
  menu_w = term_w/2;
  int menu_x = (term_w / 4), menu_y = (term_h / 4);


  edit_h = (term_h * 0.90);
  edit_w = (term_w * 0.90);
  bg_win = newwin(term_h, term_w, 0, 0);
  edit_win = derwin(bg_win, edit_h, edit_w, edit_x, edit_y);

  box(edit_win, '*', '*');
  touchwin(edit_win);
  keypad(bg_win, true);
  keypad(edit_win, true);


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
  refresh();

  mvwprintw(menu_win, 2, (menu_w/2)-4, "My Menu");
  mvwprintw(bg_win, 0, 0, "F1: Menu");
  mvwprintw(bg_win, 0, (term_w/2)-18, "CSCI 1730 Editor");

  mvwprintw(bg_win, term_h-1, 0, filename.c_str());

  mvwprintw(edit_win, edit_y, edit_x, "Replace this at some point.");
  file_to_screen(load_file(fileptr), edit_win, edit_h, edit_w);

  wrefresh(bg_win);
  wrefresh(edit_win);
  int ch = 9;
  while(ch != KEY_UP){
    ch = wgetch(edit_win);
    switch(ch){
    case KEY_F(1):
      cur_item = current_item(main_menu);
      bool open = init_menu_window(main_menu, menu_win, cur_item);
      if(open == false){
	//mvwprintw(bg_win, 0, (term_w/2)-18, "OH SHIT"); 
         unpost_menu(main_menu);
	 wrefresh(bg_win);
         wrefresh(edit_win);
      }
      break;
    }
    wrefresh(bg_win);
    wrefresh(edit_win);
  }
  unpost_menu(main_menu);
  for(int i=0; i<4; i++){
    free_item(items[i]);
  }
  free_menu(main_menu);
  delwin(menu_subwin);
  delwin(menu_win);
  delwin(edit_win);
  delwin(bg_win);;
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
  for(int i = 0; i < data.size(); i++){
    int ct = 0;
    char ch = data[i];
    mvwprintw(win, x, y, "%c", ch);
    if(y == (width - 1) || ch == '\n'){
      x++;
      y = 1;
      mvwprintw(win, x, y,"%c", '\n');
    }
    y++;
    
  }
 
}

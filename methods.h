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
string load_file(string filename);
bool close_file(int &fd);
void run_editor(const char * fileptr);
string get_filename(const char * fileptr);
void file_to_screen(string data, WINDOW * win, int h, int w);
int show_menu_window(int menu_h, int menu_w, int menu_y, int menu_x);
//void type(WINDOW *win, int x, int y, int h, int w);
string add_char(char ch, string data);
string remove_char(string s);

string get_filename(const char * fileptr){
  if (fileptr == nullptr){
    return "Untitled";
  }
  else {
    string fn = fileptr;
    return fn;
  }
}


string load_file(string filename){
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

	  if(buffer[i] != '\n'){
	   	data += buffer[i];
	  }
      	}
    }
    return data;
  }
}

/*off_t getOffset(char * fileptr){
  return lseek(fileptr, 0, SEEK_END);
*/

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



void run_editor(const char *fileptr){
  WINDOW *term_win;
  WINDOW *edit_win;
  string filename = get_filename(fileptr);
  
  //off_t offset = lseek(fileptr, 0, SEEK_END);
  
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

  //FIGURE OUT PADS?
  //edit_win = newpad(edit_h,edit_w); 
  
  touchwin(edit_win);

  keypad(term_win, true);
  keypad(edit_win, true);

  refresh();

  mvwprintw(term_win, 0, 0, "F1: Menu");
  mvwprintw(term_win, 0, (term_w/2)-18, "CSCI 1730 Editor");
  mvwprintw(term_win, (term_h-1), 0, filename.c_str());

  string text = load_file(filename);
  file_to_screen(text, edit_win, edit_h, edit_w);

   
  wrefresh(term_win);
  wrefresh(edit_win);
  //prefresh(edit_win, edit_y,edit_x, edit_y,edit_x, edit_h, edit_w);
  box(edit_win, '*', '*');
  int key = 1;
  while(key != KEY_UP){
    key = wgetch(edit_win);
    text = add_char(key, text);
    file_to_screen(text, edit_win, edit_h, edit_w);

    switch(key){
    case KEY_F(1):
      int selection = show_menu_window(menu_h, menu_w, menu_y, menu_x);
      wrefresh(term_win);
      

      if(selection == 0 || selection == 2){
	 wrefresh(term_win);
         wrefresh(edit_win);	 
      }
      else if(selection == 1){
	mvwprintw(edit_win, 200, 100, "%c", 'o');
      }
      /*else if(selection == 2){
       mvwprintw(edit_win, 200, 100, "%c", 's');
       }*/
      else if(selection == 3){
	mvwprintw(edit_win,0,0, "%c", 'a');
      }
      else if(selection == 4){
	mvwprintw(edit_win, 200, 100, "%c", 'e');
      }
      break;
    }
    wrefresh(term_win);
    // wrefresh(edit_win);
  }
  delwin(edit_win);
  delwin(term_win);;
  endwin();
}

/*void type(WINDOW *win, int offset){
  
  }*/

string add_char(char ch, string data){
  if(ch == 0x08){
    //return remove_char(data);
    return (data + '&');
  } else {
    return (data+ch);
  }
}

string remove_char(string s){
  string data = "";
  for(int i = 0; i < (s.size() - 1); i++){
    data[i] = s[i];
  }
  return data;
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
 
  wrefresh(menu_win);

  cbreak();

  int key = 1;
  int choice = 0;

  post_menu(main_menu);
  wrefresh(menu_win);
  ITEM *cur_item = NULL;
  bool selected = false;
  while(key != KEY_F(1) && !selected){
    
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
      // menu_driver(main_menu,REQ_TOGGLE_ITEM);
      cur_item = current_item(main_menu);
      selected = true;
      break;
    }
    wrefresh(menu_win);
  }
  unpost_menu(main_menu);
  for(int i=0; i < n_choices; i++){
    free_item(items[i]);
  }
 wborder(menu_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wrefresh(menu_win);
  //mvprintw(2, (menu_w/2)-4, NULL);
  wrefresh(menu_win);
  free_menu(main_menu);
  wrefresh(menu_win);
  delwin(menu_subwin);
  delwin(menu_win);
  endwin();
  const char * it = (const char *) &cur_item;
  if(strcmp(it,"Open") == 0){
    choice = 1;
  } else if (strcmp(it,"Save") == 0){
    choice = 2;
  } else if (strcmp(it,"Save As") == 0){
    choice = 3;
  } else if (strcmp(it,"Exit") == 0){
    choice = 4;
  }
  return choice; //USER EXITS MENU (F1 Pressed)
}




void file_to_screen(string data, WINDOW * win, int height, int width){
  int x = 1;
  int y = 1;
  int w = width - 1;
  for(int i = 0; i < data.size(); i++){
    char ch = data[i];
   
      mvwprintw(win, x, y, "%c", ch);
      if(y == (w - 1) || ch == '\n'){
	x++;
	y = 1;
	//mvwprintw(win, x, y,"%c", '\n');
      }
      y++;
  }
  mvwprintw(win, x, y, "%c", '\0');
}



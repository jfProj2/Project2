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
//IN ORDER, SIMPLEST FIRST
string load_file(string filename);
bool close_file(int &fd);
string get_filename(const char * fileptr);
void run_editor(const char * fileptr);
string add_char(char ch, string data); //NEW
string remove_char(string s); //NEW
bool file_exists(const char * fileptr); //NEW
void file_to_screen(string data, WINDOW * win, int h, int w);
void save_file(string filename, string data); //NEW
int show_menu_window(int menu_h, int menu_w, int menu_y, int menu_x);
void run_editor(const char * fileptr);
int show_alert_window(int code, int h, int w, int y, int x); //NEW

/**returns string of chars in file
   TO DO: error handling */
string load_file(string filename){
  //took away O_CREAT so we don't auto create files
  //(made more sense for project)
  int fd = open(filename.c_str(), O_RDWR | O_APPEND);
  if(fd < 0){
    //ERROR CHECK HERE
    //int errorNum = errno;
    //error window
    //return int referring to type of error
    return "";
  }else{
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
}

/**TO DO: all destructors and stuff*/
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


string get_filename(const char * fileptr){
  if (fileptr == nullptr){
    return "Untitled";
  }
  else {
    string fn = fileptr;
    return fn;
  }
}

/**use for typing
   TO DO: figure out how to deal with weird chars
   eg arrow keys*/
string add_char(char ch, string s){
  string data = "";
  int len = s.size();
    if(ch == 127){
      if(len > 0){
	data += remove_char(s);
      }
    } else {
      data = s + ch;
    }
    return data;
}

/**use for typing backspace, doesn't really work
   TO DO: figure out how to backspace*/
string remove_char(string s){
  string data = "";
  for(int i = 0; i < (s.size() - 1); i++){
    data[i] += s[i];
  }
  s += '\b';
  return s;
}

bool file_exists(const char * fileptr){
  return(fileptr != nullptr);
}

/**TO DO: weird xy-issues*/
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
	mvwprintw(win, x, y,"%c", '\n');
      }
      y++;
  }
}

/**saves file by recreating file and writing over, basically
   TO DO: error check */
void save_file(string filename, string s){
  int fd = open(filename.c_str(),O_RDWR, O_TRUNC); //error check here
  string data = s;
  int n = s.size();
  char * buffer = new char[n];
  buffer = (char*)data.c_str();
  if(write(fd, buffer, n) == -1){
    //error check here
  }
}

/**Menu is now interactive with enter key*/
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
  post_menu(main_menu);
  wrefresh(menu_win);

  int key = 1;
  int choice = 0;
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
    case '\n':
      //MORE TO DO HERE?
      selected = true;
      break;
    }
    wrefresh(menu_win);
  }

  if(selected){
    ITEM *cur_item = current_item(main_menu);
    const char * it = item_name((const ITEM*)cur_item);
    if(strcmp(it,"Open") == 0){
      choice = 1;
    } else if (strcmp(it,"Save") == 0){
      choice = 2;
    } else if (strcmp(it,"Save As") == 0){
      choice = 3;
    } else if (strcmp(it,"Exit") == 0){
      choice = 4;
    }
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
    // endwin();
    return choice; //USER EXITS MENU (F1 Pressed)
}

/**Program now only exits thru menu, alert windows started
   Save mostly works!!
   TO DO: menu logic, errors!
*/
void run_editor(const char *fileptr){
  WINDOW *term_win;
  WINDOW *edit_win;
  string filename = get_filename(fileptr);
  bool exists = file_exists(fileptr);
  initscr();
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_CYAN);
  init_pair(2, COLOR_WHITE, COLOR_MAGENTA);
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

  //FIGURE OUT PADS? Not sure if necessary.
 
  touchwin(edit_win);
  keypad(term_win, true);
  keypad(edit_win, true);
  refresh();
  attron(COLOR_PAIR(1));  //Attempting to turn on color
  mvwprintw(term_win, 0, 0, "F1: Menu");
  mvwprintw(term_win, 0, (term_w/2)-8, "CSCI 1730 Editor");
  mvwprintw(term_win, (term_h-1), 0, filename.c_str());
  attroff(COLOR_PAIR(1));
  string text = load_file(filename);
  file_to_screen(text, edit_win, edit_h, edit_w);
  
  wrefresh(term_win);
  wrefresh(edit_win);
  box(edit_win, '*', '*');
  int key = 1;
  bool running = true;
  while(running){
    bool saved = false;
    key = wgetch(edit_win);
    text = add_char(key, text);
    file_to_screen(text, edit_win, edit_h, edit_w);

    switch(key){
    case KEY_F(1):
      int selection = show_menu_window(menu_h, menu_w, menu_y, menu_x);
      int alert_select;
      wrefresh(term_win);
      if(selection == 0){
	 wrefresh(term_win);
         wrefresh(edit_win);	 
      }
      else if(selection == 1){
	//open
	alert_select = show_alert_window(1,menu_h, menu_w, menu_y, menu_x);
	if(alert_select == 0){
	   wrefresh(term_win);
	   wrefresh(edit_win);
	}
      }
      else if(selection == 2){
	//save
	save_file(filename, text);
      }
      else if(selection == 3){
	//save as
	alert_select = show_alert_window(3,menu_h, menu_w, menu_y, menu_x);
	if(alert_select == 0){
	   wrefresh(term_win);
	   wrefresh(edit_win);
	}
      }
      else if(selection == 4){
	//exit
	running = false;
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

/**New: different alerts depending on the situation
   TO DO: they won't disappear, menu options
   PLAN: return an int (0 to exit, like with menu func)
   For ex, user selected open -> "no" to save changes -> returns 3, maybe
   or user selected save as -> "yes" to overwrite -> returns 8, maybe
   NEED ALL OPTIONS OF WHAT USER COULD DO HERE
 */
int show_alert_window(int code, int h, int w, int y, int x){
  WINDOW * alert_win = newwin(h,w,y,x);
  //WINDOW * alert_subwin;
  string mssg = "";
  // MENU * alert_menu;
  int key = 1;
  int choice = 0;
  if(code == 1){
    mssg += "Save Changes?";
  }else if(code == 2){
    mssg += "Enter file name: ";
  }else if(code == 3){
    mssg += "Overwrite file?";
  }
  box(alert_win, '*', '*');
  initscr();
  mvwprintw(alert_win, 1, (w/2)-(mssg.size()/2), mssg.c_str());
  cbreak();
  wrefresh(alert_win);
  int ch;
  if((ch = getch()) != KEY_F(1)){
    wrefresh(alert_win);
  }
  wrefresh(alert_win);
  delwin(alert_win);
  return choice;

}










//can open existing file
//save file
//exit
//menu can be used
//typing - not backspace or random keys
//newlines weird when reopening
  
  
  
  
  




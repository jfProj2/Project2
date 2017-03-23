#include <ncurses.h>
#include <menu.h>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

//FAKE FAKE

//menu options
const char* choices[] = {"Open","Save","Save As", "Exit"};
WINDOW* editwin;
  WINDOW* menuwin;
  WINDOW* menusub;
  
  MENU *menu;
  ITEM **items;
  ITEM *cur_item;
WINDOW* win;

WINDOW* init_main_windows();

//WINDOW* create_err_win();

bool init_menu(MENU* m, WINDOW *mwin);

void exit();

int main(const int argc, const char *argv[]){

  int ch;
  if(argc > 2){
    cout << "Too many files" << endl;
    // win = create_err_win(); 
  }else{
    win = init_main_windows();
    while((ch = getch()) != KEY_UP)
    {
       switch(ch){
       case KEY_F(1):

       	bool open = init_menu(menu,menuwin);
	if(!open){
	  unpost_menu(menu);
	  refresh();
	  wrefresh(win);
	  wrefresh(editwin);
	}
	  

	}
    }
  exit();
  return EXIT_SUCCESS;

}
}

WINDOW* init_main_windows(){
  
  //windows
 
  


  //sizes of main, edit, and menu windows (error same as menusize)
  int height, width;
  int eheight,ewidth, ex, ey;
  int mheight,mwidth, mx, my;
  int ch;
  
  //will be from the user input
  string filename = "file name";

  string title ="CSCI 1730 EDITOR";

  initscr();
  cbreak();
  keypad(stdscr,true); //gimme da keyz
  noecho();
    
  
  getmaxyx(stdscr, height, width); //size of screen

  
  eheight = height*.95;
  ewidth = width*.95;          //SIZEZ YO
  ex = ey = 1;

  mheight = height/2;
  mwidth = width/2;
  mx = (width/4);
  my = (height/4);
  
  win = newwin(height, width, 0, 0); //window with same size  
  editwin = derwin(win,eheight,ewidth,ex,ey); //where text edited
  
  box(editwin, 0, 0); 
  keypad(win,true);
  keypad(editwin,true);   

  int n_choices= sizeof(choices);
  items = (ITEM**)calloc(n_choices+1,sizeof(ITEM*));
  for(int i = 0; i < n_choices; i++){
    items[i] = new_item(choices[i], NULL);
  }
  items[n_choices] = (ITEM*)NULL;
  menu = new_menu((ITEM**)items);
  
  menuwin = newwin(mheight,mwidth,my,mx);
  menusub = derwin(menuwin,mheight/2,mwidth/2,mheight*.4,mwidth/3);
  keypad(menuwin,true);
  set_menu_win(menu,menuwin);
  set_menu_sub(menu,menusub);

  mvwprintw(menuwin,2,(mwidth/2)-4,"Muh Menu");
  set_menu_mark(menu, "> ");
  box(menuwin,0,0);
  refresh();

  //I like this text 'cause it never moves...
  mvwprintw(win, 0,0, "F1: Menu");
  mvwprintw(win, 0, (width/2)-(title.size()/2), title.c_str());

  //this text will depend on the name of the file
  mvwprintw(win,height-1, 0, filename.c_str()); //IO HERE

   mvwprintw(editwin, ey, ex, "edit here"); //REMOVE 

  wrefresh(win);
  wrefresh(editwin); 

  return win;
    
    
 
}



//enabled scrolling
//to do: close menu, connect actions to menu items.
bool init_menu(MENU* m, WINDOW* mwin){
  int c;
        post_menu(m);
        wrefresh(mwin);
	bool open = false;
	char * choice;
	while((c = wgetch(mwin)) != KEY_F(1)){
	  //open = true;
	  switch(c){

	  case KEY_DOWN:
	    menu_driver(m, REQ_DOWN_ITEM);
	    break;
	  case KEY_UP:
	    menu_driver(m, REQ_UP_ITEM);
	    break;
	  case 10:
	    char temp[200];
	    ITEM **items;
	    items = menu_items(m);
	    
	   

	  }
	  
	  ITEM * current = current_item(m);
	  
	  wrefresh(mwin);
	  
	}
	unpost_menu(m);
	delwin(mwin);
	return false;
	

}

 void exit(){
   
   delwin(menuwin);
   delwin(menusub);
   free_menu(menu);
   for(int i = 0; i < sizeof(choices); i++){
     free_item(items[i]);
   }
   delwin(editwin);
   delwin(win);
   endwin();
 }



/*
User runs command ./1730ed
Window initialized
 if argc = 1: main win, filename = null, menu on
 if argc = 2: main win, filename from command, menu off
 if argc > 2: err win - try again?
Open file with open/read/write 
Can edit on editor





Window var = reg/err
function for toggle menu?
*/

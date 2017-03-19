#include <ncurses.h>
#include <menu.h>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

//FAKE FAKE

//menu options
const char* choices[] = {"Open","Save","Save As", "Exit"};


void init_menu(MENU* m, WINDOW *mwin);
//WINDOW* create_err_win(int height, int width, int my, int mx, bool open);
int main(const int argc, const char *argv[]){

  //windows
  WINDOW* win;
  WINDOW* editwin;
  WINDOW* menuwin;
  WINDOW* menusub;
  
  MENU *menu;
  ITEM **items;
  ITEM *cur_item;


  //sizes of main, edit, and menu windows (error same as menusize)
  int height, width;
  int eheight,ewidth, ex, ey;
  int mheight,mwidth, mx, my;
  int ch;
    

//  bool menuopen = false;

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
  keypad(editwin,true);    //GIMME KEYS YO
   // post_menu(menu);

  int n_choices= sizeof(choices);
  items = (ITEM**)calloc(n_choices+1,sizeof(ITEM*));
  for(int i = 0; i < n_choices; i++){
    items[i] = new_item(choices[i], NULL);
  }
  items[n_choices] = (ITEM*)NULL;
  menu = new_menu((ITEM**)items);
  //create_menu(menu);
  menuwin = newwin(mheight,mwidth,my,mx);
  menusub = derwin(menuwin,mheight/2,mwidth/2,mheight/3,mwidth/3);
  keypad(menuwin,true);
  set_menu_win(menu,menuwin);
  set_menu_sub(menu,menusub);
  mvwprintw(menuwin,2,(mwidth/2)-4,"Muh Menu");
  set_menu_mark(menu, "> ");
  box(menuwin,0,0);
  box(menusub,0,0);
  refresh();

  //I like this text 'cause it never moves...
  mvwprintw(win, 0,0, "F1: Menu");
  mvwprintw(win, 0, (width/2)-(title.size()/2), title.c_str());

  //this text will depend on the name of the file
  mvwprintw(win,height-1, 0, filename.c_str()); //IO HERE

  mvwprintw(editwin, ey, ex, "edit here"); //REMOVE 

  wrefresh(win);
  wrefresh(editwin); 

  //for now key up exits program
 while((ch = getch()) != KEY_UP)
    {
      switch(ch){
      case KEY_F(1): //This opens menu
             /* menuopen = true;
              menuwin = create_menu_win(mheight, mwidth, my, mx, menuopen);
              wrefresh(menuwin);
              refresh();
              wrefresh(win);
              wrefresh(editwin);
              delwin(menuwin);
              break;*/
	init_menu(menu,menuwin);
      }
    }
    
    free_menu(menu);
    for(int i = 0; i < n_choices; i++){
        free_item(items[i]);
    }
  //delwin(menuwin);*/
  delwin(editwin);
  delwin(win);
  endwin();
  return EXIT_SUCCESS;
}

//pretty effing broken :,,,(
//menu opens...but it can't close :,(
//IO HERE

/*WINDOW* create_menu_win(int height, int width, int my, int mx, bool menuopen){
  WINDOW * m = newwin(height,width,my,mx);
  int c;
  box(m, 0, 0);
  keypad(m,true);
  mvwprintw(m,1,mx/2,"MENU ^..^");
  mvwprintw(m,2,mx/2,"Open");
  mvwprintw(m,3,mx/2,"Save");
  mvwprintw(m,4,mx/2,"Save As");
  mvwprintw(m,5,mx/2,"Exit");
  wrefresh(m);
  while((c = getch()) != KEY_LEFT){
    
  }
  return m;
 }
*/

//enabled scrolling
//to do: close menu, connect actions to menu items.
void init_menu(MENU* m, WINDOW* mwin){
  int c;
        post_menu(m);
        wrefresh(mwin);
	while((c = wgetch(mwin)) != KEY_F(1)){
	  
	  switch(c){

	  case KEY_DOWN:
	    menu_driver(m, REQ_DOWN_ITEM);
	    break;
	  case KEY_UP:
	    menu_driver(m, REQ_UP_ITEM);
	    break;

	  }

	}
	unpost_menu(m);
	

}

   
 


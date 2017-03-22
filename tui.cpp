/**
PROJECT 2
**************

File: tui.cpp

Date: 3/16/2017

Authors: Ryan Joiner (810638856)
         Emma Fick   (810609119)

Prof. Michael Cotterell
**************

<NEED DESCRIPTION>

This is the implementation file for the tui class's methods...

<NEED DESCRIPTION>
**/

//INCLUDES
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

#include "io.h"
#include "tui.h"

using namespace std;

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

TUI::~TUI(){
  unpost_menu(main_menu);
  free_menu(main_menu);
  for(int i=0; i<4; i++){
    free_item(items[i]);
  }
  delwin(menu_subwin);
  delwin(menu_win);
  delwin(edit_win);
  delwin(bg_win);
  endwin();

  //IF IMPLEMENTING FILE I/O in the (tui) class

  //FileDesc = close(FileDesc);
  //if(FileDesc < 0){
  //int errorNum = errno;
  //printf("\ncat: [%s]: Error.\n",fileName.c_str());
  //printf("errno: %i - %s\n\n",errorNum, strerror(errorNum));
  //}
  
}

TUI::TUI(){

  const char* choices[] = {"Open","Save","Save As", "Exit"};
  int n_choices = ARRAY_SIZE(choices);
  int term_h, term_w;
  int edit_h, edit_w;
  int menu_h, menu_w;
  cout << "calling constructor" << endl;
  initscr();
  cbreak();
  noecho();
  getmaxyx(stdscr, term_h, term_w);
  cout << "calling" << endl;
  int edit_x = 1, edit_y = 1;
  int menu_x = (term_w / 4), menu_y = (term_h / 4);

 
  edit_h = (term_h * 0.90);
  edit_w = (term_w * 0.90);
  cout << term_h << " " << term_w << endl;
  bg_win = newwin(term_h, term_w, 0, 0);
  edit_win = derwin(bg_win, edit_h, edit_w, edit_x, edit_y); 

  box(edit_win, '*', '*');
  touchwin(edit_win);
  keypad(bg_win, true);
  keypad(edit_win, true);

  items = (ITEM**)calloc(n_choices+1, sizeof(ITEM*));
  for(int i = 0; i < n_choices+1; i++){
    items[i] = new_item(choices[i], choices[i]);
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

  mvwprintw(bg_win, term_h-1, 0, "<N/A>"); 

  mvwprintw(edit_win, edit_y, edit_x, "Replace this at some point.");
  
  wrefresh(bg_win);
  wrefresh(edit_win);
  int ch = 9;
  while((ch = getch()) != KEY_UP){
    switch(ch){
    case KEY_F(1):
      bool open = init_menu_window(main_menu, menu_win);
      if(!open){
	unpost_menu(main_menu);
	refresh();
	wrefresh(bg_win);
	wrefresh(edit_win);
      }
      break;
    }
    wrefresh(bg_win);
    wrefresh(edit_win);
  }
      
}





TUI::TUI(string fileName){

  const char* choices[] = {"Open","Save","Save As", "Exit"};
  int term_h, term_w;
  int edit_h, edit_w;
  int menu_h, menu_w;

  initscr();
  cbreak();
  noecho();
  getmaxyx(stdscr, term_h, term_w);
  int edit_x = 1, edit_y = 1;
  int menu_x = (term_w / 4), menu_y = (term_h / 4);

  edit_h = (term_h * 0.90);
  edit_w = (term_w * 0.90);

  bg_win = newwin(term_h, term_w, 0, 0);
  edit_win = derwin(bg_win, edit_h, edit_w, edit_x, edit_y);

  box(edit_win, '*', '*');
  touchwin(edit_win);
  keypad(bg_win, true);
  keypad(edit_win, true);

  items = (ITEM**)calloc(4, sizeof(ITEM*));
  for(int i = 0; i < 4; i++){
    items[i] = new_item(choices[i], NULL);
  }
  items[3] = (ITEM *)NULL;

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

  mvwprintw(bg_win, term_h-1, 0, fileName.c_str());

  mvwprintw(edit_win, edit_y, edit_x, "Replace this at some point.");

  wrefresh(bg_win);
  wrefresh(edit_win);
}

bool TUI::init_menu_window(MENU* menu, WINDOW* win){
  int c;
  post_menu(menu);
  wrefresh(win);
  bool open = false;
  while((c = wgetch(win)) != KEY_F(1)){
    //open = true;
    switch(c){

    case KEY_DOWN:
      menu_driver(menu, REQ_DOWN_ITEM);
      break;
    case KEY_UP:
      menu_driver(menu, REQ_UP_ITEM);
      break;


    }
    ITEM * current = current_item(menu);

    wrefresh(win);

  }
  unpost_menu(menu);
  endwin();
  return false;
}


/**
PROJECT 2
**************

File: tui.h

Date: 3/16/2017

Authors: Ryan Joiner (810638856)
         Emma Fick   (810609119)

Prof. Michael Cotterell
**************

<NEED DESCRIPTION>

This is the header file for the 'tui' class functions...
<NEED DESCRIPTION>

**/

//INITIALIZE THE HEADER GUARD
#ifndef TUI_H
#define TUI_H

//INCLUDES
#include <iostream>
#include <iomanip>
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

using namespace std;

class TUI {
 private:
  //inst vars
  WINDOW *bg_win;
  WINDOW *edit_win;
  WINDOW *menu_win;
  WINDOW *menu_subwin;

  MENU *main_menu;
 
  ITEM **items;
  ITEM *cur_item;

  //const char* choices[] = {"Open","Save","Save As", "Exit"};

 public:

  /**Opens initial tui with no file specified**/
  TUI();

  /**Opens initial tui with file specified**/
  TUI(string fileName);

  /**Opens tui with file specified in menu**/
  //TUI(int FileDesc);

  /**Destructor*/
  ~TUI();

  //WINDOW* create_main_win();
  //WINDOW* create_menu_win();
  //WINDOW* create_err_win();
  

};


#endif

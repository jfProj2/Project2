#ifndef TUI_H
#define TUI_H
#include <iostream>
#include <string>
#include <ncurses.h>
#include "io.h"

using namespace std;

class tui {

  //inst vars
  WINDOW *main_win;
  //WINDOW *menu_win; //If these windows aren't always here, should they be
  //WINDOW *err_win;  // instance vars? 
  FILE* file
  

 public:

  /**Opens initial tui with no file specified**/
  tui();

  /**Opens initial tui with file specified**/
  tui(const char * fileptr);

  /**Opens tui with file specified in menu**/
  tui(FILE* f);

  /**Destructor*/
  ~tui();
  WINDOW *create_main_win();
  WINDOW *create_menu_win();
  WINDOW *create_err_win();
  

};


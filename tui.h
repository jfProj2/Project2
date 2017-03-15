#ifndef TUI_H
#define TUI_H
#include <iostream>
#include <string>

using namespace std;

class tui {

  //inst vars
  io();

 public:

  /**Opens tui with no file specified**/
  tui();

  /**Opens tui with file specified**/
  tui(const char * fileptr); 

  /**Destructor*/
  ~tui();
  createMainWin();
  createMenu();
  createErrWin();

};


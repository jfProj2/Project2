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
#include <cerrno>
#include <fstream>
#include <string>
#include <cstdio>
#include <ncurses.h>
#include "io.h"

using namespace std;

class TUI {
  private:
  //inst vars
   WINDOW *main_win;
  //WINDOW *menu_win; //If these windows aren't always here, should they be
  //WINDOW *err_win;  // instance vars? 
   FILE* File;
  

 public:

  /**Opens initial tui with no file specified**/
  TUI();

  /**Opens initial tui with file specified**/
  TUI(const char * fileptr);

  /**Opens tui with file specified in menu**/
  TUI(FILE* f);

  /**Destructor*/
  ~TUI();
  WINDOW *create_main_win();
  WINDOW *create_menu_win();
  WINDOW *create_err_win();
  

};


/**
PROJECT 2
**************

File: main.cpp

Date: 3/16/2017

Authors: Ryan Joiner (810638856)
         Emma Fick   (810609119)

Prof. Michael Cotterell
**************

<NEED DESCRIPTION>

This is the main method for Project2.

<NEED DESCRIPTION>
**/

//INCLUDES
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <curses.h>
#include <ncurses.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#include "io.h"
#include "tui.h"

using namespace std;

//Prototype for the main with arguments
int main(const int argc, const char * argv[]);

int main(const int argc, const char * argv[]){
  int errorNum = 0;

  if(argc == 1){
    TUI *editor = new TUI();
    while(true);
  }
  else if(argc == 2){
    int FileDesc = IO::openFile(argv[1]);
    //If failure to open, create an error window inside the editor
    /** 
    if(FileDesc < 0){
      errorNum = errno;
      printf("1730ed: [%s]: Error.\n", argv[1].c_str());
      printf("errno: %i - %s\n\n", errorNum, strerror(errorNum));
      return EXIT_FAILURE;
    }
    else{


    }
    **/
  }
  else{
    printf("ERROR: Too many arguments to ./1730ed\n");
    printf("Retry run command with proper syntax\n\n");
    printf("Ex: ./1730ed   or   ./1730ed filename.txt\n");
    return EXIT_FAILURE;
  }

  return 22;
}





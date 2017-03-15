/**
PROJECT 2
#########
Fick-Joiner Productions
#########
Due: March 27th, 2017 @ 11:55 PM
Professor: Michael Cotterell

File: main.cpp
#########
<FINISH DESCRIPTION>
This is the main file...Check
<FINISH DESCRIPTION>
**/

#include <iostream>
#include <iomanip>
#include <ncurses.h>
#include <menu.h>
#include <cstdlib>
#include "io.h"
#include "tui.h"

using namespace std;

int main(const int argc, const char * argv[]) //At somepoint we need to include execution-time parameters to the main method
//like in lab, argc will give us 1 if correct, argv[0] will be initial file to open (first time - not open in menu)
{
  if(argc != 1)
  {
    cout << "You must enter one file name." << endl;
  }
  else
  {
   // Tui(argv[0]); //Opens ncurses window
    cout << "Testing: file name entered:" << endl;
  }
  return 22; //Returning this # is my habit :P
}

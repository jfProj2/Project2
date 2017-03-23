/**

DESCRIPTIONS NEEDED

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

#include "methods.h"

using namespace std;

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int main(const int argc, const char * argv[]);

void run_editor(string fileName);

bool init_menu_window(MENU* menu, WINDOW* win, ITEM* current);



int main(const int argc, const char * argv[]){
  //int errorNum = 0;
  if(argc == 1){

    run_editor("no file");

  }
  else if(argc == 2){
    //int FileDesc = IO::openFile(argv[1]);
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

/**

PROJECT 2
**************

File: io.h

Date: 3/15/2017

Authors: Ryan Joiner (810638856)
         Emma Fick   (810609119)

Prof. Michael Cotterell
**************

<NEED DESCRIPTION>

This is the header file for the 'io' class functions...
<NEED DESCRIPTION>


**/
//CREATE THE HEADER GUARD
#ifndef IO_H
#define IO_H

//INCLUDES
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <cstdio>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

//DECLARE SHENANIGANS
using namespace std;

class IO{
  
 public:
  
  //OPEN FILE (rw-)
  static int openFile(string fileName);

  //CLOSE THE FILE
  static int closeFile(int &FileDesc);

  //GET THE NUMBER OF LINES OF TEXT IN THE FILE
  static int getNumberOfLines(int FileDesc);

  //RETURN THE CONTENTS OF THE FILE
  static string getFileContents(int FileDesc);
};

#endif //FINISH THE HEADER GUARD

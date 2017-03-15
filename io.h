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
#include <cerrno>
#include <cstdio>
#include <fstream>

//DECLARE SHENANIGANS
using namespace std;

class IO{
  
 public:
  
  //OPEN FILE (rw-)
  static FILE* openFile(string fileName);

  //CLOSE THE FILE
  static bool closeFile(string fileName, FILE* openFile);

  //GET THE NUMBER OF LINES OF TEXT IN THE FILE
  int getNumberOfLines(FILE* openFile)

  //RETURN THE CONTENTS OF THE FILE
  string getFileContents(FILE* openFile, int numLinesOfOuput);
};

#endif //FINISH THE HEADER GUARD

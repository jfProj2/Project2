/**
PROJECT 2
**************

File: io.cpp

Date: 3/15/2017

Author: Ryan Joiner (810638856)
        Emma Fick   (810609119)

Prof. Michael Cotterell
**************

<NEED DESCRIPTION>

This is the method...

<NEED DESCRIPTION>
**/

//INCUDES
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <cstdio>
#include <fstream>
#include "io.h"
#include "tui.h"

using namespace std;

static FILE* IO::openFile(string fileName){
  FILE * File = fopen(fileName.c_str(), "rw");
  return File;
}


static bool IO::closeFile(string fileName, FILE* openFile){
  fclose(openFile);
}


static int IO::getNumberOfLines(FILE* openFile){
  char dataReader;
  int numLinesOfOutput = 0;
  while((dataReader = fgetc(openFile)) != EOF){
    if(dataReader == '\n')
      numLinesOfOutput += 1;
  }
  return numLinesOfOutput;
}


static string IO::getFileContents(FILE* openFile){
  string data = "";
  char dataReader;
  while((dataReader = fgetc(openFile)) != EOF){
    data += dataReader;
  }
  return data;
}



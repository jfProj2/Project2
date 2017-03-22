/**
PROJECT 2
**************

File: io.cpp

Date: 3/16/2017

Authors: Ryan Joiner (810638856)
         Emma Fick   (810609119)

Prof. Michael Cotterell
**************

<NEED DESCRIPTION>

This is the method...

<NEED DESCRIPTION>
**/

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
#include "io.h"
#include "tui.h"

using namespace std;


//Need to handle error return values inside the main
int IO::openFile(string fileName){
  int FileDesc  = open(fileName.c_str(), O_RDWR);

  return FileDesc;
}

//Need to handle error return values inside the main
int IO::closeFile(int &FileDesc){
  FileDesc = close(FileDesc);

  return FileDesc; 
}

//This method is called after the parameter is already error checked
int IO::getNumberOfLines(int FileDesc){
  int numLinesOfOutput = 0;
  size_t bytes_read;
  unsigned char buffer[1024];
  int errorNum = 0;
  do{

    bytes_read = read(FileDesc, buffer, sizeof(buffer));

    for(unsigned int i = 0; i < bytes_read; i++)
      if(buffer[i]  == '\n')
	numLinesOfOutput += 1;

  }while(bytes_read == sizeof(buffer));
  
  return numLinesOfOutput;
}


//This method is called after the parameter is already error-checked
string IO::getFileContents(int FileDesc){
  string data = "";
  
  size_t bytes_read;
  unsigned char buffer[1024];
  int errorNum = 0;
  do{

    bytes_read = read(FileDesc, buffer, sizeof(buffer));

    for(unsigned int i = 0; i < bytes_read; i++)
      data += string(1, buffer[i]);

  }while(bytes_read == sizeof(buffer));

  return data;
}



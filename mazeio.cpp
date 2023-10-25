/*
mazeio.cpp
*/

#include <iostream>
#include <fstream>
#include "mazeio.h"
using namespace std;
 
//read the infile using iostream. Return in any case of incorrect formatting.
char** read_maze(char* filename, int* rows, int* cols)
{
  ifstream ifile(filename); //opening file

  if ( ifile.fail() ) //checking if fail open
  {
    return NULL;
  }
  
  ifile >> *rows >> *cols; //reading rows and cols

  if ( ifile.fail () ) //checking if failed
  {
    return NULL;
  }

  char** mazeArray = new char* [*rows]; //creation of mazeArray (on heap)

  for (int i = 0; i < *rows; i++)
  {
    mazeArray[i] = new char[*cols];
  }

  for (int i = 0; i < *rows; i++)
  {
    for (int j = 0; j < *cols; j++)
    {
      ifile >> mazeArray[i][j]; 
    }
  }

  return mazeArray; //returning mazeArray
}

//print maze function
void print_maze(char** maze, int rows, int cols)
{
  cout << rows << ' ' << cols << endl; //printing rows and cols
  for (int i = 0; i < rows; i++) //printing maze
  {
    for (int j = 0; j < cols; j++)
    {
      cout << maze[i][j];
    }
    cout << endl;
  }
}

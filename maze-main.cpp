/*
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"
using namespace std;

// *********************************************************************************************
// **************************** All Prototypes *************************************************
// *********************************************************************************************
int maze_search(char**, int, int);
bool invalidChar(char**, int, int);
bool invalidMaze(char**, int, int);
void backtraceAndDeallocate(Location**, char**, char**, Location, Location, int);

// *********************************************************************************************
// **************************** Main, Begin ****************************************************
// *********************************************************************************************
int main(int argc, char* argv[]) 
{
  //-----------------Start: read infile, check if valid, call function to read maze ----------
    int rows, cols, result;
    char** mymaze=NULL;
    const char* invalid_char_message = "Error, invalid character.";
    const char* invalid_maze_message = "Invalid maze.";
    const char* no_path_message = "No path could be found!";

    if(argc < 2) //if there isn't an input file:
    {
        cout << "Please provide a maze input file" << endl;
        return -1;
    }

    mymaze = read_maze(argv[1], &rows, &cols); //read maze

    //-----------------End: read infile, check if valid, call function to read maze ----------

    // ------------Start: checks for invalid character or invalid maze ---------------------
      if (invalidChar((char**)mymaze, rows, cols) == true) //invalidChar checker
      {
        cout << invalid_char_message;
        for (int i = 0; i < rows; i++)
        {
          delete [] mymaze[i];
        }
        delete [] mymaze;
        return 0;
      }

      if (invalidMaze((char**)mymaze, rows, cols) == true) //invalidMaze checker
      {
        cout << invalid_maze_message;
        for (int i = 0; i < rows; i++)
        {
          delete [] mymaze[i];
        }
        delete [] mymaze;
        return -1;
      }

    // ------------End: checks for invalid character or invalid maze ---------------------

    // ------------Start: Search the maze, check if path, print the maze --------
    result = maze_search((char**)mymaze, rows, cols); //putting maze search in result value

    if ( result == 0 ) //checking if no path found
    {
      cout << no_path_message;
      for (int i = 0; i < rows; i++)
      {
        delete [] mymaze[i];
      }
      delete [] mymaze;
      return 0;
    }
    else //checking if path found. printing maze if so. 
    {
      print_maze((char**)mymaze, rows, cols);
    }
    // ------------End: Search the maze, check if path, print the maze --------

    //---------------Start: Final step. Everything worked, deallocate memeory ------------
    for (int i = 0; i < rows; i++)
    {
      delete [] mymaze[i];
    }
    delete [] mymaze;
    return 0; //main return
    //---------------End: Final step. Everything worked, deallocate memeory ------------
}

// *********************************************************************************************
// **************************** Main, End ******************************************************
// *********************************************************************************************



// *********************************************************************************************
// **************************** Maze_Search, Begin *********************************************
// *********************************************************************************************
int maze_search(char** maze, int rows, int cols)
{
  //-----------------Start: find the start and finish locations ------------------------
  Location start, finish;
  start.row = -1; start.col = -1; //initilizing start
  finish.row = -1; finish.col = -1; //initilizing finish

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (maze[i][j] == 'S')
      {
        start.row = i;
        start.col = j;
      }
      if (maze[i][j] == 'F')
      {
        finish.row = i;
        finish.col = j;
      }
    }
  }

  //-----------------Start: find the start and finish locations ------------------------

  //-----------------Start: Create the Queue, add start to the Queue -------------------
  Queue myQueue(rows*cols);//queue of size row*col

  myQueue.add_to_back(start);//adding start to queue

  //-----------------End: Create the Queue, add start to the Queue ---------------------

  //-----------------Start: Create and allocate predecessor and visited ----------------
  Location** predecessor = new Location* [rows]; //predecessor creation

  for (int i = 0; i < rows; i++)
  {
    predecessor[i] = new Location[cols]; 
  }

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      predecessor[i][j].row = -1;
      predecessor[i][j].col = -1;
    }
  }

  bool** visited =  new bool* [rows]; //visited creation

  for (int i = 0; i < rows; i++)
  {
    visited[i] = new bool[cols];
  }

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      visited[i][j] = false;
    }
  }

  //-----------------End: Create and allocate predecessor and visited ----------------

  // ************************************ Maze Loop Time! *************************************
  Location curr; //Declare curr
  while (!myQueue.is_empty())
  {
    curr = myQueue.remove_from_front(); //remove curr from front of queue
    // --------------------North--------------------
    if (curr.row >= 1) //if in bounds: 
    {
      curr.row -= 1;
      if (curr.row == finish.row && curr.col == finish.col) //if finish:
      {
        curr.row += 1;
        backtraceAndDeallocate((Location**)predecessor, (char**)maze, (char**)visited, curr, start, rows ); 
        return 1;
      }
      else if (maze[curr.row][curr.col] == '.' && visited[curr.row][curr.col] == false) //else if valid space:
      {
        myQueue.add_to_back(curr);
        visited[curr.row][curr.col] = true;
        predecessor[curr.row][curr.col].row = curr.row + 1;
        predecessor[curr.row][curr.col].col = curr.col;
      }
    curr.row += 1;
    }
    
    // --------------------West--------------------

    if (curr.col >= 1) //if in bounds: 
    {
      curr.col -= 1;
      if (curr.row == finish.row && curr.col == finish.col) //if finish:
      {
        curr.col += 1;
        backtraceAndDeallocate((Location**)predecessor, (char**)maze, (char**)visited, curr, start, rows ); 
        return 1;
      }
      else if (maze[curr.row][curr.col] == '.' && visited[curr.row][curr.col] == false) //else if valid space:
      {
        myQueue.add_to_back(curr);
        visited[curr.row][curr.col] = true;
        predecessor[curr.row][curr.col].row = curr.row;
        predecessor[curr.row][curr.col].col = curr.col + 1;
      }
    curr.col += 1;
    }
    // --------------------South--------------------
    if (curr.row < rows - 1) //if in bounds: 
    {
      curr.row += 1;
      if (curr.row == finish.row && curr.col == finish.col) //if finish:
      {
        curr.row -= 1;
        backtraceAndDeallocate((Location**)predecessor, (char**)maze, (char**)visited, curr, start, rows ); 
        return 1;
      }
      else if (maze[curr.row][curr.col] == '.' && visited[curr.row][curr.col] == false) //else if valid space:
      {
        myQueue.add_to_back(curr);
        visited[curr.row][curr.col] = true;
        predecessor[curr.row][curr.col].row = curr.row - 1;
        predecessor[curr.row][curr.col].col = curr.col;
      }
    curr.row -= 1;
    }

    // --------------------East--------------------
    if (curr.col < cols - 1) //if in bounds: 
    {
      curr.col += 1;
      if (curr.row == finish.row && curr.col == finish.col) //if finish:
      {
        curr.col -= 1;
        backtraceAndDeallocate((Location**)predecessor, (char**)maze, (char**)visited, curr, start, rows ); 
        return 1;
      }
      else if (maze[curr.row][curr.col] == '.' && visited[curr.row][curr.col] == false) //else if valid space:
      {
        myQueue.add_to_back(curr);
        visited[curr.row][curr.col] = true;
        predecessor[curr.row][curr.col].row = curr.row;
        predecessor[curr.row][curr.col].col = curr.col - 1;
      }
      curr.col -= 1;
    }
  }
  // **************************** Maze Loop End **************************
  return 0; //return 0 if no path found
}
// *********************************************************************************************
// **************************** Maze_Search, End ***********************************************
// *********************************************************************************************


// *********************************************************************************************
// **************************** InvalidChar, Begin *********************************************
// *********************************************************************************************
bool invalidChar(char** maze, int rows, int cols)
{
  //looping through each value in maze
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (maze[i][j] != '.' && maze[i][j] != 'S' && maze[i][j] != 'F' && maze[i][j] != '#') //checking if there is an unrecognized char
      {
        return true;
      }
    }
  }
  return false;
}
// *********************************************************************************************
// **************************** InvalidChar, End **********************************************
// *********************************************************************************************



// *********************************************************************************************
// **************************** InvalidMaze, Begin *********************************************
// *********************************************************************************************
bool invalidMaze(char** maze, int rows, int cols)
{
  int startCount = 0; int finishCount = 0; //startCount and finishCount, which will count the number of S and F. 

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (maze[i][j] == 'S')
      {
        startCount++;
      }
      else if (maze[i][j] == 'F')
      {
        finishCount++;
      }
      if (startCount > 1 || finishCount > 1) //if there are >1 S or F
        return true;
      }
    }

    if (startCount == 0 || finishCount == 0) // if there aren't one of S or F
    {
      return true;
    }
  return false;
}
// *********************************************************************************************
// **************************** InvalidMaze, End **********************************************
// *********************************************************************************************



// *********************************************************************************************
// **************************** backtraceAndDeallocate, Begin **********************************
// *********************************************************************************************
void backtraceAndDeallocate(Location** predecessor, char** maze, char** visited, Location curr, Location start, int rows)
{
  while (curr.row != start.row || curr.col != start.col) //backtrack loop. fills in * to found path.
  {
    maze[curr.row][curr.col] = '*';
    Location next = predecessor[curr.row][curr.col];
    curr = next;
  }

  for (int i = 0; i < rows; i++) //deallocate loop. deallocates visited nad predecessor, which were declared in maze_search
  {
    delete [] visited[i];
    delete [] predecessor[i];
  }
  delete [] visited;
  delete [] predecessor;
}
// *********************************************************************************************
// **************************** backtraceAndDeallocate, End ************************************
// *********************************************************************************************

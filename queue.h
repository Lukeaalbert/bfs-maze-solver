/* 
queue.h

Declares two new data types,
- Location, a data type containing a row and column number
- Queue, a list of Locations organized chronologically
*/

#ifndef QUEUE_H
#define QUEUE_H


struct Location {
   int row;
   int col;
};

// a class that contains a series of Locations
class Queue {
public: // API:
   
   // constructor.
   Queue(int maxlen);
   
   // destructor.
   ~Queue();
   
   // insert a new Location at the end/back of our list   
   void add_to_back(Location loc);

   // return and "remove" the oldest Location not already extracted
   Location remove_from_front();

   // is this Queue empty?
   bool is_empty();

   // member variables of an Queue, for implementation:
private:
   Location* contents; // ptr to dynamically-allocated array
   int tail;
             
   int head; 
            
};

#endif

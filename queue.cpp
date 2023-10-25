/*
queue.cpp
*/

#include "queue.h"

//Constructor function. Creating tail, head, and contents.
Queue::Queue(int maxlen) {
    head = 0;
    tail = 0;
    contents = new Location[maxlen];
}

//Destructor. releases resources. C++ will call it automatically.
Queue::~Queue() {
    delete [] contents;
}

//Insert a new Location at the end/back of our list
void Queue::add_to_back(Location loc) {
    contents[tail] = loc;
    tail++;
}

//Return and "remove" the oldest Location not already extracted
Location Queue::remove_from_front() {
    int returnHead = head;
    head++;
    return contents[returnHead];
}

//Check if empty
bool Queue::is_empty() {
    return head == tail;
}

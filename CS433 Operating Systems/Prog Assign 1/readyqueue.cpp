/**
 * Assignment 1: priority queue of processes
 * @file readyqueue.cpp
 * @author Andrew Ortiz and Mitchell Curtis
 * @brief ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 * @version 0.1
 */

#include <iostream>
#include "readyqueue.h"

using namespace std;

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code


/**
 * @brief Constructor for the ReadyQueue class.
 */
 ReadyQueue::ReadyQueue()  {
     //TODO: add your code here
    queue = new PCB[500];
    this->num = 0;
    this->capacity = 500;
 }

/**
 *@brief Destructor
*/
 ReadyQueue::~ReadyQueue() {
     //TODO: add your code to release dynamically allocate memory
     for (int i = 0; i < num; ++i) {
         queue[i].~PCB();
     }
     delete[] queue;
 }


//copy constructor
ReadyQueue::ReadyQueue(const ReadyQueue& other) {
    // Deep copy the queue
    capacity = other.capacity;
    num = other.num;
    queue = new PCB[capacity];
    for (int i = 0; i < num; ++i) {
        queue[i] = other.queue[i];
    }
}

//equals operator
ReadyQueue& ReadyQueue::operator=(const ReadyQueue& other) {
    if (this != &other) {
        delete[] queue;
        capacity = other.capacity;
        num = other.num;
        queue = new PCB[capacity];
        for (int i = 0; i < num; ++i) {
            queue[i] = other.queue[i];
        }
    }
    return *this;
}

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
//TODO: add your code here
// When adding a PCB to the queue, you must change its state to READY.
PCB* temp = pcbPtr;
temp->setState(ProcState::READY); // set state of new PCB 

//now add the PCB and update heap
queue[num] = *temp;
//queue[num].display();
num++;
build_max_heap(); // remax heap
}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    //TODO: add your code here
    // When removing a PCB from the queue, you must change its state to RUNNING.
    PCB temp = queue[0];
    temp.setState(ProcState::RUNNING);
    queue[0] = queue[num - 1]; // swap last and remove 
    queue[num - 1] = temp; // last in queue gets the removed PCB then shift num back to the heap

    num--; // shift n back to heap
    build_max_heap(); // rebuild max heap because the last value is now at queue[o]

    return &queue[num];
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
    //TODO: add your code here
    int temp = num;
    return temp; // return size I had a temp returned here cause i was trying to debug and thought maybe their was something wrong here
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
    //TODO: add your code here
    if (num == 0)
    {
        //cout << "The queue has none" << endl; 
        // do nothing if the queue is empty
    }
    else
    {
        for (int i = 0; i < num; i++)
        {
            queue[i].display();
        }
    }
}

void ReadyQueue::max_heapify(int i)
{
    int left = (2 * i) + 1; // index of the left child 
    int right = (2 * i) + 2; // index of the right child
    int largest = i; // index of the largest priority

    // check the 3 indexes for the largest priority
    if (queue[left].getPriority() > queue[largest].getPriority() && left < num) // check left less than large and make sure left is in bounds
    {
        largest = left;
    }
    //repeat for right
    if (queue[right].getPriority() > queue[largest].getPriority() && right < num)
    {
        largest = right;
    }

    // now check if largest was changed to check for a swap and a recursive call
    if (largest != i)
    {
        PCB temp = queue[i]; // swap largest and i 
        queue[i] = queue[largest];
        queue[largest] = temp;

        max_heapify(largest); // remax heap at swapped index
    }
}

void ReadyQueue::build_max_heap()
{
    // for each non leaf node of the tree 
        //call max_heapify to turn the smallest substrees into max heaps
    for (int i = num / 2 - 1; i >= 0; i--)
    {
        max_heapify(i);
    }
}

void ReadyQueue::bubbleUp(int i)
{
    // for inserting instead of rebuilding an entire heap just bubble it up
    int start = i / 2 - 1;
    bool bubble = true;

    while (bubble == true)
    {
        max_heapify(start);
        start = start / 2 - 1;
        if (start < 0)
        {
            bubble = false;
        }
    }
}
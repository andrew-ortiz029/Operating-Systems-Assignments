/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author Andrew Ortiz and Mitchell Curtis
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include "buffer.h"
#include <iostream>
using namespace std;

// TODO: Add your implementation of the buffer class here
Buffer::Buffer(int size)
{
    this->capacity = size; // capacity is the actual size of buffer
    this->size = 0; // size is the current amount of items in the buffer
    this->array = new buffer_item[capacity];
}

Buffer::Buffer(Buffer& copy) // copy constructor
{
    this->capacity = copy.capacity;
    this->size = copy.size;
    this->array = new buffer_item[capacity];
    this->array = copy.array;
}

Buffer Buffer::operator=(Buffer const& buffer2) //operator= overload for buffer assignments
{
    this->capacity = buffer2.capacity;
    this->size = buffer2.size;
    this->array = buffer2.array;

    return *this;
}

Buffer::~Buffer()
{
    delete[] array; // free up memory allocated for array
}

bool Buffer::insert_item(buffer_item item) // return true if successful
{
    if (size == capacity)
    {
        return false;
    }else 
    {
        // bubble all items up the array 1 index and insert 
        buffer_item* temp = new buffer_item[capacity];
        temp[size] = item; // insert new item at size which would be i + 1

        for(int i = 0; i < size; i++)
        {
            temp[i] = array[i];
        }

        size++;
        array = temp; // array gets updated with item inserted
        return true;
    }
}

bool Buffer::remove_item(buffer_item *item) // return true if successful
{
    if (size == 0)
    {
        return false;
    }else 
    {
        // bubble down all items in the array 1 index and remove
        buffer_item* temp = new buffer_item[capacity];

        for(int i = 1; i < size; i++)
        {
            temp[i-1] = array[i]; // ignores first item to be removed
        }
        array = temp; // array gets updated with item removed
        size--; // update size
        return true;
    }
}

int Buffer::get_size() // return size of the buffer 
{
    return capacity;
}

int Buffer::get_count() // return number of items in the buffer
{
    return size;
}

bool Buffer::is_empty() // return true if empty
{
    if(size == 0)
    {
        return true;
    }else
    {
        return false;
    }
}

bool Buffer::is_full() // return true if full
{
    if(size == capacity)
    {
        return true;
    }else 
    {
        return false;
    }
}

void Buffer::print_buffer() // print items in the buffer
{
    if(size == 0)
    {
        cout << "Buffer: []" << endl;
    }else 
    {
        cout << "Buffer: [";
    for(int i = 0; i < size; i++)
    {
        if(i == size - 1)
        {
            cout << array[i] << "]" << endl;
        }else 
        {
            cout << array[i] << ", ";
        }
    }
    }
}
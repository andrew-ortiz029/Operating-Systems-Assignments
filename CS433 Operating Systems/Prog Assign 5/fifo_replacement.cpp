/**
* Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author Andrew Ortiz and Mitchell Curtis
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "fifo_replacement.h"
using namespace std;

// TODO: Add your implementation here
FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    // TODO: Add additional implementation code

}

// TODO: Add your implementations for desctructor, load_page, replace_page here
FIFOReplacement::~FIFOReplacement() {
    // TODO: Add necessary code here
}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    // TODO: Update your data structure FIFO replacement and pagetable
    PageEntry temp;
    temp.frame_num = num_frames;
    temp.valid = true;
    temp.dirty = false;
    page_table[page_num] = temp;
    buffer.push(page_num);
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    // TODO: Update your data structure FIFO replacement and pagetable
    int replaced_page_num = buffer.front();
    
    // remove front of buffer
    buffer.pop();

    // update the page table entry for the replaced page
    page_table[replaced_page_num].valid = false; // make as invalid

    // create new page entry for the page table
    PageEntry new_page;
    new_page.frame_num = page_table[replaced_page_num].frame_num; // reuse the frame
    new_page.valid = true; // mark new page as valid
    new_page.dirty = false;

    // update the page table with the new entry
    page_table[page_num] = new_page;

    // Add the index of the new page to the back of the buffer
    buffer.push(page_num);

    return replaced_page_num;
}
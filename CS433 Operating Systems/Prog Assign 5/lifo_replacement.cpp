/**
* Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author Andrew Ortiz and Mitchell Curtis
 * @brief A class implementing the Last in First Out (LIFO) page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "lifo_replacement.h"

// TODO: Add your implementation here
LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    // TODO: Add additional implementation code
}

// TODO: Add your implementations for desctructor, load_page, replace_page here
LIFOReplacement::~LIFOReplacement() {
    // TODO: Add necessary code here
}

// Access an invalid page, but free frames are available
void LIFOReplacement::load_page(int page_num) {
    // TODO: Add necessary code here
    PageEntry temp;
    temp.frame_num = num_frames;
    temp.valid = true;
    temp.dirty = false;
    page_table[page_num] = temp;
    buffer.push(page_num);
}

// Access an invalid page and no free frames are available
int LIFOReplacement::replace_page(int page_num) {
    int replaced_page_num = buffer.top();
    
    // remove top of buffer
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

    // Add the index of the new page to the top of the buffer
    buffer.push(page_num);

    return replaced_page_num;
}
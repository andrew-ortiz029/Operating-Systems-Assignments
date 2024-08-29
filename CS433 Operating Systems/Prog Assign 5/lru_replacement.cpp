/**
* Assignment 5: Page replacement algorithms
 * @file lru_replacement.cpp
 * @author Andrew Ortiz and Mitchell Curtis
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "lru_replacement.h"

// TODO: Add your implementation here
LRUReplacement::LRUReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    // TODO: Complete this constructor
    this->indx = 0;
}

// TODO: Add your implementations for desctructor, touch_page, load_page, replace_page here
LRUReplacement::~LRUReplacement()
{
    // TODO: Add necessary code here
}

// Accesss a page alreday in physical memory
void LRUReplacement::touch_page(int page_num)
{
    // page is in the page table need to update its position in the list
    // search the list for the page number 
    // erase that from the list and push it to the the front
    auto it = find(buffer.begin(), buffer.end(), page_num);
    buffer.erase(it);
    buffer.push_front(page_num);
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
    // page table has free frames so we just load a page 
    // create new PageEntry and insert into table
    PageEntry temp;
    temp.frame_num = num_frames;
    temp.valid = true;
    temp.dirty = false;
    page_table[page_num] = temp; // insert into page table

    //edit the map and list
    indexes[page_num] = indx; // insert pagenum and used index of the page
    indx++;
    buffer.push_front(page_num); // push the new page to the front and push everything behind it back


}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {
    // page table has no free frames now we replace
    int replaced_page_num = buffer.back();
    
    // remove top of buffer
    buffer.pop_back();

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
    buffer.push_front(page_num);
    
    // Update the current page index
    indexes[page_num] = indx;
    //[replaced_page_num] = NULL;

    return replaced_page_num;
}
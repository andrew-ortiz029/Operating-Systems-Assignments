/**
* Assignment 5: Page replacement algorithms
 * @file lru_replacement.h
 * @author Andrew Ortiz and Mitchell Curtis
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#pragma once

// Remember to add comments to your code

#include "replacement.h"
#include <unordered_map>
#include <list>
#include <algorithm>

/**
 * @brief A class to simulate the least recently used (LRU) page replacement algorithm.
 */

// for the implementation utilize a list of LRU objects (has a page number and a value for how many times its been recently touched)
// sort based on recently touched and then the front will be the least most recently used to be recplaced

class LRUReplacement : public Replacement
{
	// TODO: Add your implementation to this class
private:
        unordered_map<int, int> indexes;
        list<int> buffer; // front of the list will have the most recently used and we will push to the front to move values back that will shove the least to the back
        int indx; // index counter

public:
	/**
	 * @brief Constructor
	 * @param num_pages 
	 * @param num_frames 
	 */
	LRUReplacement(int num_pages, int num_frames);
	
    /**
    * @brief Destructor
    */
    virtual ~LRUReplacement();

    /**
     * @brief Accesss a page alreay in physical memory
     * It may be overridden in a subclass 
     * @param page_num The logical page number.
     */
    virtual void touch_page(int page_num);

    /**
     * @brief Access an invalid page, but free frames are available.
     * Assign the page to an available  frame, not replacement needed
     * @param page_num The logical page number.
     */
    virtual void load_page(int page_num);

    /**
     * @brief Access an invalid page, and there is no free frame.
     * Replace the page with the page that has been in memory the longest.
     * @param page_num The logical page number.
     * @return Selected victim page #
     */
    virtual int replace_page(int page_num);

};
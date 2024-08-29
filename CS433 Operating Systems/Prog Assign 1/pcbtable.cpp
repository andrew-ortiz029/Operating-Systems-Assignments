/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author Andrew Ortiz & Mitchell Curtis
 * @brief This is the implementation file for the PCBTable class.
 * //You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
 * // Remember to add sufficient comments to your code
 */

#include "pcbtable.h"

/**
 * @brief Construct a new PCBTable object of the given size (number of PCBs)
 *
 * @param size: the capacity of the PCBTable
 */
PCBTable::PCBTable(int size) {
   // TODO: add your code here
   this->table = new PCB[size];
   this->size = size;
   this->count = 0;
}

/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() {
   // TODO: add your code here
   // Delete all the PCBs in the table
    //for (int i = 0; i < count; ++i) {
    //    delete table[i];
    //}
   delete [] table;
}

/**
 * @brief Get the PCB at index "idx" of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx"
 */
PCB* PCBTable::getPCB(unsigned int idx) {
    // TODO: add your code here
    return &table[idx];
}

/**
 * @brief Add a PCB pointer to the PCBTable at index idx.
 *
 * @param pcb: the PCB to add
 */
void PCBTable::addPCB(PCB *pcb, unsigned int idx) {
    // TODO: add your code here
    // Add a PCB pointer to the PCBTable at index idx.
    table[idx] = *pcb;
}

void PCBTable::addNewPCB(unsigned int pid, unsigned int priority, unsigned int idx) {
    PCB* pcb = new PCB(pid, priority);
    addPCB(pcb, idx);
    this->count += 1;
    delete pcb;
}

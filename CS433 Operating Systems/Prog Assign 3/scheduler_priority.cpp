/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author Andrew Ortiz and Mitchell Curtis 
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "iostream"
#include "scheduler_priority.h"
#include <algorithm>
using namespace std;


//constructor 
SchedulerPriority::SchedulerPriority()
{
    this->AvgTurn = 0;
    this->AvgWait = 0;
}

SchedulerPriority::~SchedulerPriority(){}

void SchedulerPriority::init(std::vector<PCB>& process_list)
{
    // add a copy of the process list because the simulation will change the order of the main process list 
    this->process_list = process_list;
    this->process_list_copy = process_list;
    
    // sort the main process list
    sort(this->process_list.begin(), this->process_list.end(), [](PCB a, PCB b){return a.priority > b.priority;});
}

void SchedulerPriority::print_results()
{
    // create vectors for current wait and turn times
    vector<int> currentTurn(process_list.size());
    vector<int> currentWait(process_list.size());
    
    // print the wait and turn around times of each process
    for(int i = 0; i < process_list.size(); i++)
    {
        int turn = 0;
        int wait = 0;
        int position = 0; // keeps track of current processes wait and turn around time becuase it is a priority and doesn't go in order

        // calcualte and print current turn time
        for(int j = i; j >= 0; j--)
        {
            turn = turn + process_list[j].burst_time;
        }
        position = process_list[i].id;
        currentTurn[position] = turn;

        // calculate and print current wait time
        if(i > 0) // don't calculate wait if on the first iteration
        {
            for(int j = i-1; j >= 0; j--)
            {
                wait = wait + process_list[j].burst_time;
            }
        }
        currentWait[position] = wait;
    }

    //print results
    for(int i = 0; i < process_list_copy.size(); i++)
    {
        cout << process_list_copy[i].name << " turn-around time = " << currentTurn[i] << ", waiting time = " << currentWait[i] << endl;
    }

    // finally print the final average turn and wait time 
    cout << "Average turn-around time = " << this->AvgTurn << ", Average waiting time = " << this->AvgWait << endl;
}

void SchedulerPriority::simulate()
{
    // calculate average turnaround and wait times in simulate 
    double turn = 0;
    double wait = 0;
    
    // print each process and its time units
    for(int i = 0; i < process_list.size(); i++)
    {
        cout << "Running Process " << process_list[i].name << " for " << process_list[i].burst_time << " time units" << endl;
    }

    // calculate average wait and turn around time
    for(int i = 0; i < process_list.size(); i++)
    {
        // calculate total turn around time at each index
        for(int j = i; j >= 0; j--)
        {
            turn = turn + process_list[j].burst_time;
        }

        // calcualte total waiting time
        if(i > 0)
        {
            for(int j = i-1; j >= 0; j--)
            {
                wait = wait + process_list[j].burst_time;
            }
        }
        
    }

    // divide by size to get the average result
    turn = turn / process_list.size();
    wait = wait / process_list.size();

    this->AvgTurn = turn;
    this->AvgWait = wait;
}
/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Andrew Ortiz and Mitchell Curtis (TODO: your name)
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "iostream"
#include "scheduler_fcfs.h"

using namespace std;

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here
// constructor and destructor
SchedulerFCFS::SchedulerFCFS()
{
    this->AvgTurn = 0;
    this->AvgWait = 0;
}

SchedulerFCFS::~SchedulerFCFS(){}


void SchedulerFCFS::init(std::vector<PCB>& process_list)
{
    this->process_list = process_list;
}

void SchedulerFCFS::print_results()
{
    // print each process and its time units
    for(int i = 0; i < process_list.size(); i++)
    {
        cout << "Running Process " << process_list[i].name << " for " << process_list[i].burst_time << " time units" << endl;
    }

    // print the wait and turn around times of each process
    for(int i = 0; i < process_list.size(); i++)
    {
        int turn = 0;
        int wait = 0;

        // calcualte and print current turn time
        for(int j = i; j >= 0; j--)
        {
            turn = turn + process_list[j].burst_time;
        }

        // calculate and print current wait time
        if(i > 0)
        {
            for(int j = i-1; j >= 0; j--)
            {
                wait = wait + process_list[j].burst_time;
            }
        }

        cout << process_list[i].name << " turn-around time = " << turn << ", waiting time = " << wait << endl;
    }

    // finally print the final average turn and wait time 
    cout << "Average turn-around time = " << this->AvgTurn << ", Average waiting time = " << this->AvgWait << endl;
}

void SchedulerFCFS::simulate()
{
    double turn = 0;
    double wait = 0;

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
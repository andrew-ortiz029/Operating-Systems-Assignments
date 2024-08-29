/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Andrew Ortiz and Mitchell Curtis
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
//

#include "scheduler_rr.h"

SchedulerRR::SchedulerRR(int time_quantum)
{
    this->time_quantum = time_quantum;
    this->AvgTurn = 0;
    this->AvgWait = 0;
}

SchedulerRR::~SchedulerRR(){}

void SchedulerRR::init(std::vector<PCB>& process_list)
{
    // add a copy of the process list because the simulation will change the order of the main process list 
    this->process_list = process_list;
    vector<int> temp(process_list.size());
    this->turnTime = temp;
    this->waitTime = temp;
}

void SchedulerRR::print_results()
{
    //print results
    for(int i = 0; i < process_list.size(); i++)
    {
        cout << process_list[i].name << " turn-around time = " << turnTime[i] << ", waiting time = " << waitTime[i] << endl;
        AvgTurn += turnTime[i];
        AvgWait += waitTime[i];
    }
    
    AvgTurn = AvgTurn / process_list.size();
    AvgWait = AvgWait / process_list.size();


    // finally print the final average turn and wait time 
    cout << "Average turn-around time = " << this->AvgTurn << ", Average waiting time = " << this->AvgWait << endl;
}

void SchedulerRR::simulate()
{
    // varibles needed to run the round robin
    int currentProcess = 0;
    bool run = true;

    // calculate average turnaround and wait times in simulate 
    double turn = 0;

    // before we simulate store the burst times as a negative value in the wait time so we can get the appropiate wait time
    for(int i = 0; i < process_list.size(); i++)
    {
        waitTime[i] = waitTime[i] - process_list[i].burst_time;
    }

    while(run)
    {
        if(process_list[currentProcess].burst_time > 0)
        {
            if(process_list[currentProcess].burst_time > time_quantum)
            {
                cout << "Running Process " << process_list[currentProcess].name << " for " << time_quantum << " time units" << endl;
                process_list[currentProcess].burst_time = process_list[currentProcess].burst_time - time_quantum; // update burst time
                turn += time_quantum; // update turnaround time 

            }else 
            {
                cout << "Running Process " << process_list[currentProcess].name << " for " << process_list[currentProcess].burst_time << " time units" << endl;
                turn += process_list[currentProcess].burst_time; // update turnaround time with rest of burst
                turnTime[currentProcess] = turn; // becuase the process is complete store this in turnTime at current process
                waitTime[currentProcess] += turn; // add the turn time to the wait time (the wait time is currently - whatever the burst time is)
                process_list[currentProcess].burst_time = 0; // set burst time to 0 as the process is complete
            }   
        }
        
        //iterate and check if the current process reached the end of the list
        currentProcess++;
        if(currentProcess >= process_list.size())
        {
            currentProcess = 0;
        }

        //check condition of while loop
        run = false;;
        for(int i = 0; i < process_list.size(); i++)
        {
            if(process_list[i].burst_time > 0)
            {
                run = true;
            }
        }

    }
    
}

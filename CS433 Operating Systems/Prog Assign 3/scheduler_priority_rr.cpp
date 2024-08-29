/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.cpp
 * @author ??? (TODO: your name)
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_priority_rr.h"
#include <algorithm>

// TODO: add implementation of SchedulerPriorityRR constructor, destrcutor and 
// member functions init, print_results, and simulate here
/**
     * @brief Construct a new SchedulerPriority object
     */
    SchedulerPriorityRR::SchedulerPriorityRR(int time_quantum)
    {
        this->time_quantum = time_quantum;
        this->AvgTurn = 0;
        this->AvgWait = 0;
    }

    /**
     * @brief Destroy the SchedulerPriority object
     */
    SchedulerPriorityRR::~SchedulerPriorityRR(){}

    /**
     * @brief This function is called once before the simulation starts.
     *        It is used to initialize the scheduler.
     * @param process_list The list of processes in the simulation.
     */
    void SchedulerPriorityRR::init(std::vector<PCB>& process_list)
    {
        // add a copy of the process list because the simulation will change the order of the main process list 
        this->process_list = process_list;
        this->process_list_copy = process_list;
        vector<int> temp(process_list.size());
        this->turnTime = temp;
        this->waitTime = temp;

        // sort the main process list
        sort(this->process_list.begin(), this->process_list.end(), [](PCB a, PCB b){return a.priority > b.priority;});
    }

    /**
     * @brief This function is called once after the simulation ends.
     *        It is used to print out the results of the simulation.
     */
    void SchedulerPriorityRR::print_results()
    {
        //print results
        for(int i = 0; i < process_list.size(); i++)
        {
            cout << process_list_copy[i].name << " turn-around time = " << turnTime[i] << ", waiting time = " << waitTime[i] << endl;
            AvgTurn += turnTime[i];
            AvgWait += waitTime[i];
        }
    
        AvgTurn = AvgTurn / process_list.size();
        AvgWait = AvgWait / process_list.size();


        // finally print the final average turn and wait time 
        cout << "Average turn-around time = " << this->AvgTurn << ", Average waiting time = " << this->AvgWait << endl;
    }

    /**
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
    void SchedulerPriorityRR::simulate()
    {
        int priorityCount = 0;
        int index = 0;
        double turn = 0;

        // before we simulate store the burst times as a negative value in the wait time so we can get the appropiate wait time
        for(int i = 0; i < process_list.size(); i++)
        {
            waitTime[i] = waitTime[i] - process_list_copy[i].burst_time;
        }

        while(index < process_list.size()) // run until all processes burst times are completed
        {
            bool priorityCheck = true;
            
            while(priorityCheck) // run until all proccesses with the same priority are accounted for
            {
                // check through process list until we reach a process with a lower priority.
                if(index >= process_list.size())
                {
                    priorityCheck = false;
                }else 
                {
                    for(int i = index; i < process_list.size() - 1; i++)
                    {
                        if (process_list[i].priority == process_list[i+1].priority)
                        {
                            // cout << process_list[i].priority << " " << process_list[i+1].priority << endl;
                            priorityCount++;  
                            // cout <<"priority count is: " << priorityCount << endl;                      
                        }else
                        {
                            break;
                            priorityCheck = false;
                        }
                    }
                }
                
                priorityCheck = false;
            }

            // if priorityCount == 0 then run that processes entire burst and subtract processes left
            // else 
            // while loop with round robin algorithm with those same priority processes
            if(priorityCount == 0)
            {
                cout << "Running Process " << process_list[index].name << " for " << process_list[index].burst_time << " time units" << endl;
                turn += process_list[index].burst_time; // update turnaround time 
                turnTime[process_list[index].id] = turn; // becuase the process is complete store this in turnTime at current process
                waitTime[process_list[index].id] += turn; // add the turn time to the wait time (the wait time is currently - whatever the burst time is)
                process_list[index].burst_time = 0; // update burst time
                index++;
            }else 
            {
                bool run = true;
                int currentProcess = index; // keep track of index without updating index

                while(run)
                {
                    // rr with index and index+priority count as the bounds
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
                            turnTime[process_list[currentProcess].id] = turn; // becuase the process is complete store this in turnTime at current process
                            waitTime[process_list[currentProcess].id] += turn; // add the turn time to the wait time (the wait time is currently - whatever the burst time is)
                            process_list[currentProcess].burst_time = 0; // set burst time to 0 as the process is complete
                        }
                    }

                    //iterate and check if the current process reached the end of the list
                    currentProcess++;
                    if(currentProcess >= process_list.size())
                    {
                        currentProcess = index;
                    } else if(currentProcess > index + priorityCount)
                    {
                        currentProcess = index;
                    }

                    run = false;
                    for(int i = index; i <= index + priorityCount; i++)
                    {
                        if(process_list[i].burst_time > 0)
                        {
                            run = true;
                        }
                    }

                }

                index = index + priorityCount + 1;// update index to skip the processes that were just ran
                priorityCount = 0;
            }
        }
    }
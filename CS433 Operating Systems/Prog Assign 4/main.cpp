/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Andrew Ortiz and Mitchell Curtis
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "buffer.h"
#include <time.h> 
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

// semaphores for synchronization
pthread_mutex_t mutex; // mutex lock to prevent producer/consumer threads from accessing at the same time
sem_t fullSem; // counting semaphore to keep track of # of items in the buffer
sem_t emptySem; // another counting semaphore to keep track of # of items in the buffer

// global buffer object
Buffer buffer;

// Producer thread function
// TODO: Add your implementation of the producer thread here
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *) param);

    while (true) {
        /* sleep for a random period of time */
        usleep(rand()%1000000);
        // TODO: Add synchronization code here
        sem_wait(&emptySem); // wait till the buffer is not full
        pthread_mutex_lock(&mutex); // enter critical section

        if (buffer.insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Producer error condition"  << endl;    // shouldn't come here
        }

        pthread_mutex_unlock(&mutex); // unlock mutex
        sem_post(&fullSem); // signal full to increment
    }
}

// Consumer thread function
// TODO: Add your implementation of the consumer thread here
void *consumer(void *param) {
    buffer_item item;

    while (true) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);
        // TODO: Add synchronization code here
        sem_wait(&fullSem); // wait till the buffer is not empty
        pthread_mutex_lock(&mutex); // enter critical section

        if (buffer.remove_item(&item)) {
            cout << "Consumer " << item << ": Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer error condition" << endl;    // shouldn't come here
        }

        pthread_mutex_unlock(&mutex); // unlock mutex
        sem_post(&emptySem); // signal empty 
    }
}

int main(int argc, char *argv[]) {
    /* TODO: 1. Get command line arguments argv[1],argv[2],argv[3] */
    srand(time(0)); // seed for rand()

    // assume there argc is equal to 4 could add check not needed for this implementation
    int sleepTime = atoi(argv[1]); // sleep time from arg
    int numPThreads = atoi(argv[2]); // # of producer threads from arg 
    int numCThreads = atoi(argv[3]); // # of consumer threads from arg
    int producerID[numPThreads];
    int consumerID[numCThreads];

    /* TODO: 2. Initialize buffer and synchronization primitives */
    pthread_t ptid; // create producer threads id
    pthread_t ctid; // create consumer threads id
    pthread_mutex_init(&mutex, NULL);
    sem_init(&emptySem, 0, buffer.get_size()); // all slots are initially empty thus initialized with buffer size
    sem_init(&fullSem, 0, 0); // all slots are empty thus initialized to 0

    /* TODO: 3. Create producer thread(s).
    You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
    for(int i = 0; i < numPThreads; i++)
    {
        producerID[i] = i+1;
        pthread_create(&ptid, NULL, producer, &producerID[i]); // pass ids to threads as created
    }

    
    /* TODO: 4. Create consumer thread(s) */
    for(int i = 0; i < numCThreads; i++)
    {
        consumerID[i] = i+1;
        pthread_create(&ctid, NULL, consumer, &consumerID[i]); // pass ids to threads as created
    }

    
    /* TODO: 5. Main thread sleep */
    sleep(sleepTime);
    
    /* TODO: 6. Exit */
    exit(0);
}

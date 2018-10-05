#include "ThreadPool.h"
#include <unistd.h>
#include <iostream>

ThreadPool::ThreadPool() {

}

static void *startJobs(void *arg) {
    ThreadPool *pool = (ThreadPool *) arg;
    pool->doJobs();
    return NULL;
}

void ThreadPool::doJobs() {
    while (!stop) {
        pthread_mutex_lock(&lock);
        //if there are jobs to do
        if (!jobs_queue.empty()) {
            Job *job = jobs_queue.front();
            jobs_queue.pop();
            pthread_mutex_unlock(&lock);
            job->execute();
            TripInformation *tripInfo = (TripInformation *) job->getArg();
            //add the trip with the calculated node stack.
            tripVec.push_back(*tripInfo);
            occupied = true;
        } else {
            pthread_mutex_unlock(&lock);
            sleep(1);
            occupied = false;
        }
    }
    pthread_exit(NULL);
}

void ThreadPool::addJob(Job *job) {
    jobs_queue.push(job);
}

ThreadPool::ThreadPool(int num) {
    // TODO Auto-generated constructor stub
    threads_num = num;
    startJob();
    threads = new pthread_t[threads_num];

    pthread_mutex_init(&lock, NULL);
    //create threads
    for (int i = 0; i < threads_num; i++) {
        pthread_create(threads + i, NULL, startJobs, this);
    }
    occupied = false;
}


void ThreadPool::terminate() {
    stop = true;
}

ThreadPool::~ThreadPool() {
    // TODO Auto-generated destructor stub
    delete[] threads;
    pthread_mutex_destroy(&lock);
}

vector<TripInformation> ThreadPool::getTripVec() {
    return tripVec;
}

void ThreadPool::cleanVec() {
    tripVec.clear();
}

void ThreadPool::startJob() {
    stop = false;
}

bool ThreadPool::isOccupied() {
    return occupied;
}
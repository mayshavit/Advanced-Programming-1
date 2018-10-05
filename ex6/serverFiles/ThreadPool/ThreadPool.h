#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include "Job.h"
#include "../TripInformation.h"
#include <queue>
#include <pthread.h>

using namespace std;

/*
 *The ThreadPool class.
 * This class is responsible to create 5 threads for computing the trips.
 */
class ThreadPool {
private:
    queue<Job *> jobs_queue;
    int threads_num;
    pthread_t *threads;
    bool stop;
    pthread_mutex_t lock;
    vector<TripInformation> tripVec;
    bool occupied;
public:
    /*
     * The constructor function.
     */
    ThreadPool();

    /*
     * The constructor function.
     * Gets a number - how many threads to create.
     */
    ThreadPool(int num);

    /*
     * The destructor function.
     */
    virtual ~ThreadPool();

    /*
     * Do the jobs from the deque if it's not empty.
     */
    void doJobs();

    /*
     * Add a job to the deque.
     */
    void addJob(Job *job);

    /*
     * Stop doing jobs.
     */
    void terminate();

    /*
     * Return the trips vector.
     */
    vector<TripInformation> getTripVec();

    /*
     * Empty the trip vector.
     */
    void cleanVec();

    /*
     * Change the bool value to "true" - for starting the jobs.
     */
    void startJob();

    /*
     * Return a bool that indicates if a job is being done.
     */
    bool isOccupied();
};

#endif /* THREADPOOL_H_ */

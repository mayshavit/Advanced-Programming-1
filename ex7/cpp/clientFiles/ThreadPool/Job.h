#ifndef JOB_H_
#define JOB_H_

/*
 * The job class.
 * Responsible for doing the given function in a thread
 */
class Job {
private:
    void *arg;

    void *(*func)(void *arg);

public:
    /*
     * The constructor function.
     */
    Job();

    /*
     * The destructor function.
     */
    virtual ~Job();

    /*
     * The constructor function.
     * Gets a void* function - the function to the thread, and void* arg - the
     * data to send to the function.
     */
    Job(void *(*func)(void *arg), void *arg);

    /*
     * Do the function.
     */
    void execute();

    /*
     * Returns the arg member.
     */
    void *getArg();
};

#endif /* JOB_H_ */

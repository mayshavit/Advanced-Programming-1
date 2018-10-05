/*
 * Job.cpp
 *
 *  Created on: Jan 20, 2017
 *      Author: viki
 */

#include <iostream>
#include "Job.h"
#include "../TripInformation.h"

using namespace std;

Job::Job(void *(*func)(void *arg), void *arg) : func(func), arg(arg) {
    // TODO Auto-generated constructor stub
}

Job::Job() {

}

Job::~Job() {
    // TODO Auto-generated destructor stub
}


void Job::execute() {
    func(arg);
}

void *Job::getArg() {
    return arg;
}

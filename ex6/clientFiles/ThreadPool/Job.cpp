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
    /* TripInformation *tripInfo = (TripInformation *) arg;
     cout << "TripInfo id:" << tripInfo->getId() << ", start "
             "point:" << tripInfo->getStartPoint() << ", dst "
                  "point:" << tripInfo->getEndPoint() << endl;*/

}

Job::Job() {

}

Job::~Job() {
    // TODO Auto-generated destructor stub
}


void Job::execute() {
    //cout << "execute job" << endl;
    func(arg);
    /*TripInformation *tripInfo = (TripInformation *) arg;
    cout << "job, id #" << tripInfo->getId() << ", stack "
            "size:" << tripInfo->getNodeVec().size() << endl;*/

}

void *Job::getArg() {
    return arg;
}

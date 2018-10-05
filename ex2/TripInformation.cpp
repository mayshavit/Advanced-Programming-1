//
// Created by eliyagvili on 28/11/16.
//

#include "TripInformation.h"

TripInformation::TripInformation(int tripId, Point startP, Point endP, int pasengersNum, double tarrif) {

}
TripInformation::TripInformation() {

}

int TripInformation::getId() const {
    return 0;
}

double TripInformation::getTotalMeters() const {
    return 0;
}

Point TripInformation::getStartPoint() const {
    return Point (1,1);
}

Point TripInformation::getEndPoint() const {
    return Point(2,2);
}

int TripInformation::getPassengersNum() const {
    return 0;
}

double TripInformation::getTarrif() const {
    return 0;
}

Driver TripInformation::getDriver() const {
    return Driver(3,4,SINGLE,4);
}

void TripInformation::setDriver(Driver d) {

}


void TripInformation::updateTotalMeters(double meters) {

}

void TripInformation::updateDriverSatisfactionAndCostumers() {

}

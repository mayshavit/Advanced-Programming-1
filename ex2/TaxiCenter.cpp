//
// Created by eliyagvili on 28/11/16.
//

#include "TaxiCenter.h"

TaxiCenter::TaxiCenter() {

}

TaxiCenter::TaxiCenter(int x) {
    x = 4;

}

bool TaxiCenter::answerCall(Passenger passenger) {
    return true;
}

void TaxiCenter::sendCab(Passenger passenger) {

}

void TaxiCenter::addDriver(Driver driver) {

}

void TaxiCenter::removeDriver(Driver driver) {

}

void TaxiCenter::addCab(Cab cab) {

}

void TaxiCenter::removeCab(Cab cab) {

}

void TaxiCenter::addTrip(TripInformation trip) {

}

void TaxiCenter::removeTrip(TripInformation trip) {

}

list <Driver> TaxiCenter::getDrivers() {
    list <Driver> l;
    l.push_back(Driver(4, 4, SINGLE, 7));
    return l;
}

list <Cab> TaxiCenter::getCabs() {
    list <Cab> l;
    return l;
}

list <TripInformation> TaxiCenter::getTrips() {
    list <TripInformation> l;
    return l;
}

const map<Driver, LocationListener> TaxiCenter::getLocations() const {
    map<Driver, LocationListener> l;
    return l;
}

void TaxiCenter::addLocation(LocationListener l) {

}

void TaxiCenter::removeLocation(Driver d) {

}

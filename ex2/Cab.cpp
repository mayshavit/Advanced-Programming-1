//
// Created by eliyagvili on 28/11/16.
//

#include "Cab.h"

Cab::Cab() {

}

Cab::Cab(int cabId, double meters, Manufacturer carM, Color carColor, double caTarrif, int cabSpeed) {

}

int Cab::getId() const {
    return 0;
}

double Cab::getTarrif() const {
    return 0;
}

int Cab::getSpeed() const {
    return 0;
}


Manufacturer Cab::getCarKind() const {

    return HONDA;
}

Color Cab::getColor() const {
    return GREEN;
}

double Cab::getTotalMeters() const {
    return 0;
}

void Cab::updateTotalMeters(double totalMeters) {

}

bool Cab::isEqual(Cab c) {
    return true;
}

Point Cab::getLoaction() const {
    return Point(0, 0);
}

void Cab::setLoaction(Point loaction) {

}

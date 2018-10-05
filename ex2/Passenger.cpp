//
// Created by eliyagvili on 28/11/16.
//

#include "Passenger.h"

Passenger::Passenger() {

}

Passenger::Passenger(Point startP, Point endP) {

}

int Passenger::calcSatisfaction() {
    return 0;
}

const Point Passenger::getStartPoint() const {
    return Point(6,7);
}

const Point Passenger::getEndPoint() const {
    return Point(8,7);
}

bool Passenger::isEqual(Passenger p) {
    return false;
}

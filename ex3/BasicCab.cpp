//
// Created by eliyagvili on 28/11/16.
//

#include "BasicCab.h"


int BasicCab::getId() const {
    return id;
}

double BasicCab::getTarrif() const {
    return tarrif;
}

int BasicCab::getSpeed() const {
    return speed;
}


Manufacturer BasicCab::getCarKind() const {

    return carKind;
}

Color BasicCab::getColor() const {
    return color;
}

double BasicCab::getTotalMeters() const {
    return totalMeters;
}

void BasicCab::updateTotalMeters(double meters) {
    totalMeters += meters;
}


Node BasicCab::getLocation() const {
    return location;
}

void BasicCab::setLocation(Node givenLocaction) {
    location = givenLocaction;
}

bool BasicCab::isEqual(BasicCab bc) {
    if (id == bc.getId()) {
        return true;
    }
    return false;
}

bool BasicCab::operator==(const BasicCab &c) const {
    return id == c.id;
}

bool BasicCab::operator!=(const BasicCab &c) const {
    return !(c == *this);
}

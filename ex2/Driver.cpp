//
// Created by eliyagvili on 28/11/16.
//

#include "Driver.h"

Driver::Driver() {

}

Driver::Driver(int id2, int age2, MartialStatus status, int experiance2) {
    Grid g (4,4);
    cityGrid = g;

}


void Driver::setCab(Cab cab) {


}

void Driver::setGrid(Grid grid) {

}

void Driver::updateCostumers(int costumers) {

}

void Driver::updateSatisfaction(int satisNum) {
}

int Driver::getExperiance() const {
    return 0;
}

Cab Driver::getCabInfo() const {
    Cab c (2,3,HONDA,GREEN,6,7);
    return c;
}

int Driver::getId() const {
    return 0;
}

int Driver::getAge() const {
    return 0;
}

MartialStatus Driver::getMStatus() const {
    return SINGLE;
}

double Driver::getAvgSatisfaction() const {
    return 0;
}


int Driver::getNumOfCostumers() const {
    return 0;
}

const Grid Driver::getCityGrid() const {
   // Grid g (5,6);
    return Grid(5,6);
}

bool Driver::isEqual(Driver d2) {
    return false;
}

void Driver::addPassenger(Passenger p) {

}

void Driver::clearCurrentPassengers() {

}

list <Passenger> Driver::getCurrentPassengers() {
    list<Passenger> l (4);
    Passenger p (Point(3,2), Point(2,3));
    l.push_back(p);
    return l;
}

void Driver::updateCabLocation(Point p) {

}

stack<Node> Driver::calculateWayToCostumer(Node n) {
    std::stack<Node> s;
    s.push(Node(Point(3,4)));
    s.push(Node(Point(2,3)));
    s.push(Node(Point(2,3)));
    return s;
}

ostream &operator<<(ostream &output, Driver const &d) {

}
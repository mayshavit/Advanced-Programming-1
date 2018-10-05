#include "Driver.h"
#include "BFS.h"

Driver::Driver() {

}

Driver::Driver(int id2, int age2, MartialStatus status, int experiance2) {
    id = id2;
    age = age2;
    mStatus = status;
    experiance = experiance2;
    numOfCostumers = 0;
    avgSatisfaction = 0;
    reachedToDest = false;
    toSend = false;
    currentlyOccupied = false;
}

Driver::~Driver() {

}

void Driver::setCab(BasicCab cab) {
    cabInfo = cab;
}

void Driver::setGraph(Graph *grid) {
    cityGrid = grid;
}

void Driver::updateCostumers(int costumers) {
    numOfCostumers += costumers;
}

void Driver::updateSatisfaction(int satisNum) {
    avgSatisfaction = (avgSatisfaction + satisNum);
    if (numOfCostumers != 0) {
        avgSatisfaction = avgSatisfaction / numOfCostumers;
    }
}

int Driver::getExperiance() const {
    return experiance;
}

BasicCab Driver::getCabInfo() {
    return cabInfo;
}

int Driver::getId() const {
    return id;
}

int Driver::getAge() const {
    return age;
}

MartialStatus Driver::getMStatus() const {
    return mStatus;
}

double Driver::getAvgSatisfaction() const {
    return avgSatisfaction;
}


int Driver::getNumOfCostumers() const {
    return numOfCostumers;
}

Graph *Driver::getCityGraph() {
    return cityGrid;
}

bool Driver::isEqual(Driver d2) {
    if (id == d2.getId()) {
        return true;
    }
    return false;
}

void Driver::addPassenger(Passenger p) {
    currentPassengers.push_back(p);
}

void Driver::clearCurrentPassengers() {
    currentPassengers.clear();
}

list <Passenger> Driver::getCurrentPassengers() {
    return currentPassengers;
}

void Driver::updateCabLocation(Node n) {
    cabInfo.setLocation(n);

}


void Driver::calculateWayToCostumer(stack<Node> nodeStack) {
    int size = nodeStack.size();
    for (int i = 0; i < size; ++i) {
        if (nodeStack.top().isEqual(cabInfo.getLocation())) {
            nodeStack.pop();
            continue;
        }
        wayToCostumer.push_front(nodeStack.top());
        nodeStack.pop();
    }
}

list <Node> Driver::getWayToCostumer() {
    return wayToCostumer;
}

ostream &operator<<(ostream &output, Driver const &d) {
    output << d.cabInfo.getLocation();
}

bool Driver::operator==(const Driver &d) const {
    return id == d.id;
}

bool Driver::operator!=(const Driver &d) const {
    return !(d == *this);
}

int Driver::getRequestedCabID() {
    return requestedCabID;
}

void Driver::setRequestedCabID(int requestedCabID) {
    Driver::requestedCabID = requestedCabID;
}

void Driver::setWayToCostumer(list <Node> givenWayToCostumer) {
    wayToCostumer = givenWayToCostumer;
}

bool Driver::isReachedToDest() {
    return reachedToDest;
}

void Driver::setReachedToDest(bool rtd) {
    reachedToDest = rtd;
}

bool Driver::isToSend() {
    return toSend;
}

void Driver::setToSend(bool ts) {
    toSend = ts;
}

bool Driver::isCurrentlyOccupied() {
    return currentlyOccupied;
}

void Driver::setCurrentlyOccupied(bool co) {
    currentlyOccupied = co;
}

int Driver::getClientNum() {
    return clientNum;
}

void Driver::setClientNum(int num) {
    clientNum = num;
}

int Driver::getThreadNum() {
    return threadNum;
}

void Driver::setThreadNum(int num) {
    threadNum = num;
}

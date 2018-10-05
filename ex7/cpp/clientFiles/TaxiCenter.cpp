#include "TaxiCenter.h"
#include "BFS.h"

TaxiCenter::TaxiCenter() {

}

TaxiCenter::TaxiCenter(int x) {
    counter = 0;

}

void TaxiCenter::answerCall(int tripPlace) {
    int driverPlace = findADriverforTripPlace(
            trips.at(tripPlace).getStartPoint
                    ());
    //if there is a non-occupied driver who can take the ride.
    if (driverPlace >= 0) {
        //set the node stack of the road to the driver.
        vector<Node> nodeVec = trips.at(tripPlace).getNodeVec();
        stack<Node> nodeStack;
        int size = nodeVec.size();
        for (int i = 0; i < size; ++i) {
            nodeStack.push(nodeVec[i]);
        }
        drivers.at(driverPlace).calculateWayToCostumer(nodeStack);
        drivers.at(driverPlace).setCurrentlyOccupied(true);
        //set the driver to the trip
        trips.at(tripPlace).setDriver(drivers.at(driverPlace));
        trips.at(tripPlace).setAttachedToADriver(true);
        /**********************************************************************/
        //cout << "calc nodes for client #" << drivers.at(driverPlace)
        //        .getClientNum() << endl;
        /**********************************************************************/
    }
}

void TaxiCenter::sendCab() {
    int i;
    for (i = 0; i < trips.size(); i++) {
        if (trips.at(i).getCounter() <= counter) {
            //if the trip has no driver - attach it a driver.
            if (!trips.at(i).isAttachedToADriver()) {
                answerCall(i);
                continue;
            } else {
                Driver d = trips.at(i).getDriver();
                d.setToSend(true);
                d.setCurrentlyOccupied(true);
                list <Node> nodeList = d.getWayToCostumer();
                bool sendLocation = true;
                Node node;
                //if it is luxury cab
                if (d.getCabInfo().getSpeed() != 1) {
                    node = nodeList.front();
                    nodeList.pop_front();
                    if (node.isEqual(trips.at(i).getEndPoint())) {
                        sendLocation = false;
                    }
                }
                if (sendLocation) {
                    node = nodeList.front();
                    nodeList.pop_front();
                }

                d.updateCabLocation(node);
                d.setWayToCostumer(nodeList);
                //update the trip's driver.
                trips.at(i).setDriver(d);
                int place = findDriverPlace(d);
                //update the taxi center
                drivers.at(place) = d;
                //if the driver has reached to its point
                if (node.isEqual(trips.at(i).getEndPoint())) {
                    d.setReachedToDest(true);
                    removeDriver(d);
                    addDriver(d);
                    removeTrip(trips.at(i));
                    i--;
                }
            }
            //if it is not the time of the trip - do nothing
        } else {
            continue;
        }
    }
}


void TaxiCenter::addDriver(Driver driver) {
    drivers.push_back(driver);
}

void TaxiCenter::removeDriver(Driver driver) {
    for (int i = 0; i < drivers.size(); i++) {
        if (drivers.at(i) == driver) {
            drivers.erase(drivers.begin() + i);
            return;
        }
    }
}

void TaxiCenter::addCab(BasicCab cab) {
    cabs.push_back(cab);
}

void TaxiCenter::removeCab(BasicCab cab) {
    for (int i = 0; i < cabs.size(); i++) {
        if (cabs.at(i) == cab) {
            cabs.erase(cabs.begin() + i);
            return;
        }
    }
}

void TaxiCenter::addTrip(TripInformation trip) {
    trips.push_back(trip);
}

void TaxiCenter::removeTrip(TripInformation trip) {
    for (int i = 0; i < trips.size(); i++) {
        if (trips.at(i) == trip) {
            trips.erase(trips.begin() + i);
            return;
        }
    }
}

vector<Driver> TaxiCenter::getDrivers() {
    return drivers;
}

vector<BasicCab> TaxiCenter::getCabs() {
    return cabs;
}

vector<TripInformation> TaxiCenter::getTrips() {
    return trips;
}


BasicCab TaxiCenter::findCabByID(int id) {
    for (int i = 0; i < cabs.size(); i++) {
        if (cabs.at(i).getId() == id) {
            return cabs.at(i);
        }
    }
}

Driver TaxiCenter::findDriverByID(int id) {
    Driver d(id, 0, MARRIED, 0);
    int i = findDriverPlace(d);

    return drivers.at(i);
}

int TaxiCenter::findDriverPlace(Driver d) {
    for (int i = 0; i < drivers.size(); ++i) {
        if (d.isEqual(drivers.at(i))) {
            return i;
        }
    }
    return -1;
}

void TaxiCenter::updateGraph(Graph *g, int driverLocation) {
    //set the graph of the specified driver to be the new graph.
    drivers.at(driverLocation).setGraph(g);

}

void TaxiCenter::setATrip(TripInformation tripInfo) {
    for (int i = 0; i < trips.size(); i++) {
        if (trips.at(i).getId() == tripInfo.getId()) {
            trips.at(i) = tripInfo;
            return;
        }
    }

}

void TaxiCenter::updateDriver(Driver driver) {
    driver.setToSend(false);
    driver.setCurrentlyOccupied(false);
    driver.setReachedToDest(false);

    int driverPlace = findDriverPlace(driver);
    drivers.at(driverPlace) = driver;
}


void TaxiCenter::setDrivers(vector<Driver> givenDrivers) {
    drivers = givenDrivers;
}

int TaxiCenter::findADriverforTripPlace(Node startNode) {
    for (int i = 0; i < drivers.size(); ++i) {
        //if the driver is in the correct location
        if (drivers.at(i).getCabInfo().getLocation().isEqual(startNode)) {
            //and the driver is not occupied
            if (!drivers.at(i).isCurrentlyOccupied()) {
                return i;
            }
        }
    }
    return -1;
}

void TaxiCenter::increaseCounter() {
    counter++;
}

bool TaxiCenter::isATrip(int tripId) {
    for (int i = 0; i < trips.size(); ++i) {
        if (trips.at(0).getId() == tripId) {
            return true;
        }
    }

    return false;
}

bool TaxiCenter::isACab(int cabId) {
    for (int i = 0; i < cabs.size(); ++i) {
        if (cabs.at(0).getId() == cabId) {
            return true;
        }

    }
    return false;
}
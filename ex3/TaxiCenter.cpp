#include "TaxiCenter.h"
#include "BFS.h"

TaxiCenter::TaxiCenter() {

}

TaxiCenter::TaxiCenter(int x) {
    x = 4;

}

void TaxiCenter::answerCall() {

    for (int i = 0; i < trips.size(); ++i) {
        for (int j = 0; j < drivers.size(); ++j) {
            if (trips.at(i).getStartPoint().isEqual(drivers.at(j).getCabInfo
                    ().getLocation())) {
                trips.at(i).setDriver(drivers.at(j));
                continue;
            }
        }

    }
    sendCab();
}

void TaxiCenter::sendCab() {
    for (int i = 0; i < trips.size(); ++i) {
        stack<Node> nodeStack = trips.at(i).getDriver().calculateWayToCostumer(
                trips.at(i).getEndPoint());
        Driver d = findDriverByID(trips.at(i).getDriver().getId());
        removeDriver(d);
        //update the new location of the driver, remove him and add him again.
        d.updateCabLocation(nodeStack.top());
        addDriver(d);
        removeTrip(trips.at(i));
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
    for (int i = 0; i < drivers.size(); ++i) {
        if (drivers.at(i).getId() == id) {
            return drivers.at(i);
        }
    }
}

void TaxiCenter::updateGraph(Graph *g) {
    for (int i = 0; i < drivers.size(); ++i) {
        drivers.at(i).setGraph(g);
    }
}

#ifndef EX1_TAXICENTER_H
#define EX1_TAXICENTER_H

#include <list>
#include <map>
#include "Driver.h"
#include "Cab.h"
#include "TripInformation.h"
#include "Passenger.h"
#include "LocationListener.h"

using namespace std;

class TaxiCenter {
private:
    std::list<Driver> drivers;
    std::list<Cab> cabs;
    std::list<TripInformation> trips;
    std::map<Driver, LocationListener> locations;
public:

    /*
     * The TaxiCenter constructor.
     */
    TaxiCenter();

    /*
     * The TaxiCenter constructor.
     * Gets  a x.
     */
    TaxiCenter(int x);

    /*
     * This function gets a passenger. It checks if there are enough cabs/drivers.
     * If there are - we return true. If there are not, we print something and return false.
     */
    bool answerCall(Passenger passenger);

    /*
     * In this function we look at the location map we have. We check who is the closest
     * driver, and if it is not occupied (by the trips list we have - if he is not in one
     * of the trips). Then, we call the calculateWayToCostumer in the driver.
     * We add the passengers to the driver, create new tripinformaion with the given
     * parameters and make our way with the cab.
     */
    void sendCab(Passenger passenger);

    /*
     * Function that gets a driver and adds it to the drivers list.
     */
    void addDriver(Driver driver);

    /*
     * Function that gets driver and removes it from the drivers list.
     */
    void removeDriver(Driver driver);

    /*
     * Function that returns the drivers list.
     */
    list <Driver> getDrivers();

    /*
     * Function that gets a cab and adds it to the cabs list.
     */
    void addCab(Cab cab);

    /*
     * Function that gets cab and removes it from the cabs list.
     */
    void removeCab(Cab cab);

    /*
     * Function that returns the cabs list.
     */
    list <Cab> getCabs();

    /*
     * Function that gets a trip and adds it to the trips list.
     */
    void addTrip(TripInformation trip);

    /*
     * Function that gets trip and removes it from the trips list.
     */
    void removeTrip(TripInformation trip);

    /*
     * Function that returns the trips list.
     */
    list <TripInformation> getTrips();

    /*
     * Function that returns the location map of the drivers in the taxi center.
     */
    const map<Driver, LocationListener> getLocations() const;

    /*
     * Function that adds location to the map of locations.
     */
    void addLocation(LocationListener l);

    /*
     * Function that gets a Driver, and removes it from the locations' map.
     */
    void removeLocation(Driver d);
};


#endif
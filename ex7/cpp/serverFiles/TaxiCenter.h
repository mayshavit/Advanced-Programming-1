#ifndef EX1_TAXICENTER_H
#define EX1_TAXICENTER_H

#include <list>
#include <map>
#include "Driver.h"
#include "Cab.h"
#include "TripInformation.h"
#include "Passenger.h"

using namespace std;

/*
 * The TaxiCenter class.
 * creates a taxi center.
 */
class TaxiCenter {
private:
    vector<Driver> drivers;
    vector<BasicCab> cabs;
    vector<TripInformation> trips;
    int counter;
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
     * This function attaches a trip to a driver.
     */
    void answerCall(int tripPlace);

    /*
     * This function calls the callculateWayToCostumer in the driver's class,
     * remove him from the Taxi-Center, then updates the driver location,
     * add add the updated driver again.
     * him from the
     */
    void sendCab();

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
    vector<Driver> getDrivers();

    /*
     * Function that gets a cab and adds it to the cabs list.
     */
    void addCab(BasicCab cab);

    /*
     * Function that gets cab and removes it from the cabs list.
     */
    void removeCab(BasicCab cab);

    /*
     * Function that returns the cabs list.
     */
    vector<BasicCab> getCabs();

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
    vector<TripInformation> getTrips();

    /*
     * Function that gets a Driver, and removes it from the locations' map.
     */
    void removeLocation(Driver d);

    /*
     * Function that find a cab by its id.
     * Gets an id.
     */
    BasicCab findCabByID(int id);

    /*
     * Function that finds  driver by its id.
     * Gets an id.
     */
    Driver findDriverByID(int id);

    /*
     * Function that update the graph.
     * get a graph.
     */
    void updateGraph(Graph *g, int driverLocation);

    /*
     * Function that gets a driver id, and returns its place in the drivers'
     * list.
     */
    int findDriverPlace(Driver d);

    /*
     * Function that gets a tripInformation, and updates the trips.
     */
    void setATrip(TripInformation tripInfo);

    /*
     * Function that updates the driver parameters in the drivers vector.
     */
    void updateDriver(Driver driver);

    /*
     * Function that sets the taxi-center's drivers to be the given drivers.
     */
    void setDrivers(vector<Driver> givenDrivers);

    /*
     * Function that finds a non-occupied driver for a trip.
     * Gets a start node, for finding the driver in the trip's location.
     */
    int findADriverforTripPlace(Node startNode);

    /*
     * The increaseCounter function.
     * This function increases the counter member by 1.
     */
    void increaseCounter();

    /*
     * The isATrip function.
     * This function gets a number - an id trip, and returns if the trip
     * is already attached to the taxi-center.
     */
    bool isATrip(int tripId);

    /*
     * The isACab function.
     * This funcions gets a number - an id cab, and returns if the cab
     * is already attached to the taxi-center.
     */
    bool isACab(int cabId);
};


#endif
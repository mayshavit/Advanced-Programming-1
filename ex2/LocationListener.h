#ifndef EX1_LOCATIONLISTENER_H
#define EX1_LOCATIONLISTENER_H


#include "Driver.h"

class LocationListener {
private:
    Driver driver;
public:
    /*
     * The LocationListener constructor.
     */
    LocationListener();

    /*
     * The LocationListener constructor.
     * Gets a driver.
     */
    LocationListener(Driver d);

    /*
     * Function that gets a point and updates the driver's location.
     */
    void updateDriversLocation(Point p);

    /*
     * Function that returns the driver.
     */
    const Driver getDriver() const;

};


#endif
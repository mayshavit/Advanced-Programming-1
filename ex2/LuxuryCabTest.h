#ifndef EX1_LUXURYCAB_H
#define EX1_LUXURYCAB_H


#include "Cab.h"

class LuxuryCab : public Cab {
public:
    /*
     * The LuxuryCab constructor.
     */
    LuxuryCab();

    /*
     * The LuxuryCab constructor.
     * Gets a cabId, meters, car manufacturer, color, tarrif and car speed.
     */
    LuxuryCab(int cabId, double meters, Manufacturer carM, Color carColor, double tarrif, int cabSpeed);

    /*
     * Function that updates the speed.
     */
    void updateSpeed();
};


#endif
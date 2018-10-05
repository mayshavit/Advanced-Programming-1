#ifndef EX1_LUXURYCAB_H
#define EX1_LUXURYCAB_H


#include "Cab.h"

class LuxuryCab : public BasicCab {
public:
    /*
     * The LuxuryCab constructor.
     */
    LuxuryCab();

    LuxuryCab(int cabId, Manufacturer carM, Color carColor);

    /*
     * The LuxuryCab constructor.
     * Gets a cabId, meters, car manufacturer, color, tarrif and car speed.
     */
    LuxuryCab(int cabId, double meters, Manufacturer carM, Color carColor,
              double carTarrif, int cabSpeed);

};


#endif
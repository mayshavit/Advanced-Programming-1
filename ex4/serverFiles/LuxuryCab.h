#ifndef EX1_LUXURYCAB_H
#define EX1_LUXURYCAB_H


#include "BasicCab.h"

class LuxuryCab : public BasicCab {
public:
    /*
     * The LuxuryCab constructor.
     */
    LuxuryCab();

    ~LuxuryCab();

    LuxuryCab(int cabId, Manufacturer carM, Color carColor);

    /*
     * The LuxuryCab constructor.
     * Gets a cabId, meters, car manufacturer, color, tarrif and car speed
     */
    LuxuryCab(int cabId, double meters, Manufacturer carM, Color carColor,
              double carTarrif, int cabSpeed);

    /*
     * Function that serializes the luxury cab.
     */
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<BasicCab>(*this);
    }

};


#endif
#ifndef EX1_CAB_H
#define EX1_CAB_H

#include "BasicCab.h"

class Cab : public BasicCab {
public:

    /*
     * The Cab constructor.
     */
    Cab();

    /*
     * The Cab destructor.
     */
    ~Cab();

    /*
     * The Cab constructor.
     * Gts a cab is, manufacturer and color.
     */
    Cab(int cabId, Manufacturer carM, Color carColor);

    /*
     * The Cab constructor.
     * Gets cab id, meters, manufacturer, color, tarrif and cab speed.
     */

    Cab(int cabId, double meters, Manufacturer carM, Color carColor,
        double caTarrif, int cabSpeed);


    /*
    * Function that serializea a Cab.
    */
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<BasicCab>(*this);
    }

};


#endif
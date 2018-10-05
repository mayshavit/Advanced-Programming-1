#ifndef EX1_CAB_H
#define EX1_CAB_H

#include "Point.h"

enum Manufacturer {
    HONDA = 0, SUBARO = 1, TESLA = 2, FIAT = 3
};
enum Color {
    RED = 0, BLUE = 1, GREEN = 2, PINK = 3, WHITE = 4
};

class Cab {
protected:
    int id;
    double totalMeters;
    double tarrif;
    int speed;
    Manufacturer carKind;
    Color color;
    Point loaction;
public:

    /*
     * The Cab constructor.
     */
    Cab();

    /*
     * The Cab constructor.
     * Gets cab id, meters, manufacturer, color, tarrif and cab speed.
     */
    Cab(int cabId, double meters, Manufacturer carM, Color carColor, double caTarrif, int cabSpeed);

    /*
     * Function that returns the cab kind.
     */
    Manufacturer getCarKind() const;

    /*
     *  Function that returns the cab color.
     */
    Color getColor() const;

    /*
     *  Function that returns the cab id.
     */
    int getId() const;

    /*
     *  Function that returns the tarrif.
     */
    double getTarrif() const;

    /*
     *  Function that returns the cab speed.
     */
    int getSpeed() const;

    /*
     *  Function that returns the total meters.
     */
    double getTotalMeters() const;

    /*
     * function that gets total meters and updates it.
     */
    void updateTotalMeters(double totalMeters);

    /*
     * Function that returns true if the two cabs are equal, else false.
     */
    bool isEqual(Cab c);

    /*
     * Function that returns the location.
     */
    Point getLoaction() const;

    /*
     * Function that gets point and updates the cab location.
     */
    void setLoaction(Point loaction);
};


#endif
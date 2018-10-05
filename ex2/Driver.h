#ifndef EX1_DRIVER_H
#define EX1_DRIVER_H


#include <list>
#include "Point.h"
#include "Grid.h"
#include "Cab.h"
#include "Passenger.h"
#include <stack>

enum MartialStatus {
    SINGLE, MARRIED, DIVORCED, WIDOWED
};

class Driver {
private:
    int id;
    int age;
    MartialStatus mStatus;
    int experiance;
    double avgSatisfaction;
    Cab cabInfo;
    int numOfCostumers;
    Grid cityGrid;
    list <Passenger> currentPassengers;
public:
    /*
     * The Driver constructor.
     */
    Driver();

    /*
     * The Driver constructor.
     * Gets id, age, martial status and experiance.
     */
    Driver(int id2, int age2, MartialStatus status, int experiance2);

    /*
     * Function that sets the cab.
     */
    void setCab(Cab cab);

    /*
     * Function that sets the grid.
     */
    void setGrid(Grid grid);

    /*
     * Function that gets a num of costumers, and updates the number.
     */
    void updateCostumers(int costumers);

    /*
     * Function that gets satisfaction number, and updates it.
     */
    void updateSatisfaction(int satisNum);

    /*
     * This function is called by the taxi center.
     * Inside this function we create a bfs instance. Then, we call the bfs function inside the bfs,
     * with a node that represents current location of the driver, a queue, a graph and a destination node
     * (that we receive from the taxi-center). We calculate the best way to costumer by it.
     * Then, we call the fasterRoad function inside the bfs, it returns a stack of nodes with the best
     * road. That is also the returned value of this -calculateWayToCostumer - function.
     */
    stack<Node> calculateWayToCostumer(Node n);

    /*
     * Function that returns true if the two drivers are equal, else false.
     */
    bool isEqual(Driver d2);

    /*
     * Function that gets a passenger, and adds it.
     */
    void addPassenger(Passenger p);

    /*
     * Function that clears the passengers' list.
     */
    void clearCurrentPassengers();

    /*
     * Function that returns a list of the passengers.
     */
    list <Passenger> getCurrentPassengers();

    /*
     * Function that returns the cab.
     */
    Cab getCabInfo() const;

    /*
     * Function that returns the id.
     */
    int getId() const;

    /*
     * Function that returns the age.
     */
    int getAge() const;

    /*
     * Function that returns the maritial status.
     */
    MartialStatus getMStatus() const;

    /*
     * Function that returns the experiance.
     */
    int getExperiance() const;

    /*
     * Function that returns the avarge satisfaction.
     */
    double getAvgSatisfaction() const;

    /*
     * Function that returns the number of costumers.
     */
    int getNumOfCostumers() const;

    /*
     * Function that returns the grid.
     */
    const Grid getCityGrid() const;

    /*
     * Function that gets a point and updates the cab's location.
     */
    void updateCabLocation(Point p);

    /*
     * Function that prints the driver's location.
     */
    friend ostream &operator<<(ostream &output, const Driver &d);

};


#endif
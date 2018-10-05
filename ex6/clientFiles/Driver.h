#ifndef EX1_DRIVER_H
#define EX1_DRIVER_H


#include <list>
#include "Point.h"
#include "Grid.h"
#include "Cab.h"
#include "Passenger.h"
#include <stack>
#include <boost/serialization/deque.hpp>
#include <boost/serialization/list.hpp>

using namespace boost::archive;

/*
 * The Driver class.
 * creates a driver.
 */

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
    BasicCab cabInfo;
    int numOfCostumers;
    Graph *cityGrid;
    list <Passenger> currentPassengers;
    list <Node> wayToCostumer;
    bool reachedToDest;
    bool toSend;
    int requestedCabID;
    bool currentlyOccupied;
    int clientNum;
    int threadNum;

public:

    /*
     * The Driver constructor.
     */
    Driver();

    /*
     * The Driver destructor.
     */
    ~Driver();

    /*
     * The Driver constructor.
     * Gets id, age, martial status and experiance.
     */
    Driver(int id2, int age2, MartialStatus status, int experiance2);

    /*
     * Function that sets the cab.
     */
    void setCab(BasicCab cab);

    /*
     * Function that sets the grid.
     */
    void setGraph(Graph *grid);

    /*
     * Function that gets a num of costumers, and updates the number.
     */
    void updateCostumers(int costumers);

    /*
     * Function that gets satisfaction number, and updates it.
     */
    void updateSatisfaction(int satisNum);

    /*
     * This function gets a stack of nodes - the road - and sets it to the
     * wayToCostumer member.
      */
    void calculateWayToCostumer(stack<Node> nodeStack);

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
    BasicCab getCabInfo();

    /*
     * Function that returns the id.
     */
    int getId() const;

    /*
     * Function that returns the age.
     */
    int getAge() const;

    /*
     * Function that returns the martial status.
     */
    MartialStatus getMStatus() const;

    /*
     * Function that returns the experiance.
     */
    int getExperiance() const;

    /*
     * Function that returns the avarage satisfaction.
     */
    double getAvgSatisfaction() const;

    /*
     * Function that returns the number of costumers.
     */
    int getNumOfCostumers() const;

    /*
     * Function that returns the grid.
     */
    Graph *getCityGraph();

    /*
     * Function that gets a point and updates the cab's location.
     */
    void updateCabLocation(Node n);

    /*
     * Function that returns a list of nodes  - the calculated trip.
     */
    list <Node> getWayToCostumer();

    /*
     * Function that prints the driver's location.
     */
    friend ostream &operator<<(ostream &output, const Driver &d);

    /*
     * Function that equals two drivers with the operator ==.
     */
    bool operator==(const Driver &rhs) const;

    /*
     * Function that equals two drivers with the operator !=.
     */
    bool operator!=(const Driver &rhs) const;

    /*
     * Function that returns the cab id.
     */
    int getRequestedCabID();

    /*
     * Function that sets the cab id.
     */
    void setRequestedCabID(int requestedCabID);

    /*
    * Function that sets the way to costumer.
    */
    void setWayToCostumer(list <Node> givenWayToCostumer);

    /*
     * Function that serializes the Driver.
     */
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & id;
        ar & age;
        ar & mStatus;
        ar & experiance;
        ar & avgSatisfaction;
        ar & cabInfo;
        ar & numOfCostumers;
        ar & currentPassengers;
        ar & wayToCostumer;
        ar & requestedCabID;
    }

    /*
     * function that returns true if driver ha reached to destination,
     * else return false.
     */
    bool isReachedToDest();

    /*
    * function that sets the reach to destination flag.
    */
    void setReachedToDest(bool reachedToDest);

    /*
    * function that returns true if to send the location,
    * else return false.
    */
    bool isToSend();

    /*
     * function that sets the to send flag.
     */
    void setToSend(bool toSend);

    /*
     * function that returns true if the driver is occupied,
     * else return false.
     */
    bool isCurrentlyOccupied();

    /*
     * function the sets the currently occupied flag.
     */
    void setCurrentlyOccupied(bool currentlyOccupied);

    /*
     * function that returns the client number.
     */
    int getClientNum();

    /*
    * function that sets the client number.
    */
    void setClientNum(int clientNum);

    /*
    * function that returns the thread number.
    */
    int getThreadNum();


    /*
     * function that sets the thread number.
     */
    void setThreadNum(int threadNum);

};


#endif
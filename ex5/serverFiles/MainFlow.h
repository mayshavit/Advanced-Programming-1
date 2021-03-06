#ifndef EX1_MAINFLOW_H
#define EX1_MAINFLOW_H


#include "TaxiCenter.h"
#include "sockets/Socket.h"

class MainFlow {
private:
    TaxiCenter *taxiCenter;
    Graph *graph;
    Socket *mainSocket;
    vector<Node> obstacles;


public:
    /*
     * The MainFlow constructor.
     */
    MainFlow();

    /*
     * The MainFlow constructor.
     * Gets a Taxi-Center.
     */
    MainFlow(TaxiCenter t);

    /*
     * Function that parses the trip's details and creates a trip.
     */
    void parseTrip(string str) throw(exception);

    /*
     * Function that parses the vehicle's details and creates a vehicle.
     */
    void parseVehicle(string str) throw(exception);

    /*
     * Function that gets a driver id from the user, and prints the
     * driver's location.
     */
    void printDriverLocation(string str) throw(exception);

    /*
     * Function that validates the number of obstacles given from the user.
     */
    bool validateNumOfObstacles(int numOfObstacles);

    /*
     * Function that validates the grid's parameters given from the user.
     */
    bool validateGridParameters(int x, int y);

    /*
     * The function that runs the program - there are 7 choices, every number
     * between 1-7 calls another mission.
     */
    void startFlow(const int given_port_num);

    /*
     * Function that recieves a driver via socket.
     * It opens a thread for each driver.
     */
    void recieveDrivers(int numOfDrivers);

    /*
     * This function opens a thread for calculating the trip.
     * Returns a stack of node - the road.
     */
    stack<Node> calculateATrip(TripInformation tripInfo, vector<Node>
    obstacles);

    /*
     * This function sets the main socket to be the given socket
     */
    void setMainSocket(Socket *socket);

    /*
     * This function retrns the main socket
     */
    Socket *getMainSocket();

    /*
     * A static function that gets a socket.
     * This function opens a thread for the driver, recives the driver,
     * send it the cab.
     * The thread remains open for communicating with the client.
     */
    static void *reciveADriver(void *socket);
};


#endif

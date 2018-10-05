#ifndef EX1_MAINFLOW_H
#define EX1_MAINFLOW_H


#include "TaxiCenter.h"
#include "sockets/Socket.h"
#include "ThreadPool/Job.h"
#include <vector>

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
    bool parseTrip(int gridSizeX, int gridSizeY);

    /*
     * Function that parses the vehicle's details and creates a vehicle.
     */
    void parseVehicle();

    /*
     * Function that gets a driver id from the user, and prints the
     * driver's location.
     */
    void printDriverLocation();


    /*
     * Function that validates the grid's parameters given from the user.
     * Returns (-1) if they are wrong, 1 if correct.
     */
    bool validateGridParameters(string str);

    /*
     * Function that validates the node - check if the point is in the graph.
     */
    bool validateNodeParameters(int gridSizeX, int gridSizeY,
                                int nodeSizeX, int nodeSizeY);

    /*
     * Function that validates if a given string is a valid number.
     * Returns the parsed number if the paramters are valid, else -
     * returns '-1'.
     */
    int isValidNumber(string str);

    /*
     * Function that validates if a given string is a valid char.
     * If it is - returns "true", else - returns "false".
     */
    bool isChar(string str);
    /*
     * Function that validates the number of parameters for each given string.
     */

    /*
     * Function that validates if a given string ia a double number.
     * If it is - returns the number, else - returns '-1'.
     */
    double isDouble(string str);

    int validateNumberOfParameters(string str);

    // int validateNumberOfObstacles(string str);
    /*
     * The function that runs the program - there are 7 choices, every number
     * between 1-7 calls another mission.
     */
    void startFlow(const int given_port_num);

    /*
     * Function that recieves a driver via socket.
     * It opens a thread for each driver.
     */
    void recieveDrivers(int numOfDrivers, vector<Grid *> gridVec,
                        vector<MainFlow *> mainFlowVec);

    /*
     * This function opens a thread for calculating the trip.
     * Returns a stack of node - the road.

    stack<Node> calculateATrip(TripInformation tripInfo, vector<Node>
    obstacles);*/

    /*
     * This function sets the main socket to be the given socket
     */
    void setMainSocket(Socket *socket);

    /*
     * This function returns the main socket
     */
    Socket *getMainSocket();

    /*
     * A static function that gets a socket.
     * This function opens a thread for the driver, recives the driver,
     * send it the cab.
     * The thread remains open for communicating with the client.
     */
    static void *reciveADriver(void *socket);

    /*
     * This function assigns the node stacks of the trips that were calculated
     * in the ThreadPool to the trips in the taxi-center.
     */
    void assignStacksToTripInfos(vector<TripInformation> tripVec);

    /*
     * This function deletes the grids and mainFlows that were created during
     * the program.
     */
    void deleteGridsAndMainFlows(vector<Grid *> gridVec,
                                 vector<MainFlow *> mainFlowVec);

};


#endif

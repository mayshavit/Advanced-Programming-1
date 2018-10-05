#include <iostream>
#include <queue>
#include "Point.h"
#include "MainFlow.h"
#include "sockets/Tcp.h"
#include "sockets/Tcp.h"
#include <unistd.h>

using namespace std;


/*
 * Function that parses the driver's details, and creates a driver.
 * Returns the parsed driver if the paramters were valid, else - returns NULL.
 */
Driver *parseDriver(string str);

/*
 * Function that checks if a string is a valid number.
 * Returns the parsed number if it is valid, '-1' if it's invalid.
 */
int isValidNumber(string str);

/**
 * The client main function.
 * Responsible for running the program.
 */

int main(int argc, char *argv[]) {

    string str;
    //gets the ip address from the command line.
    char *ip_address = argv[1];
    //gets the port number from the command line.
    const int port_num = atoi(argv[2]);

    //open a socket
    Socket *socket = new Tcp(0, port_num);

    //get the driver
    getline(cin, str);
    Driver *driver = parseDriver(str);

    //if there were invalid parameters
    if (driver == NULL) {
        delete driver;
        delete socket;
        return 0;
    }


    //initialize the socket
    socket->initialize();
    //attaching the driver "fake" parameters just for the serialization
    Cab c(0, HONDA, GREEN);
    c.setLocation(Node(Point(0, 0)));
    driver->setCab(c);

    //serialize  the driver
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device
            <std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();

    //"fake" integer for sending and reciving data from server via socket.
    int client = 9;

    //send the driver to the server
    socket->sendData(serial_str, client);
    char buffer[2048];

    //reciving the relevant cab
    socket->reciveData(buffer, sizeof(buffer), client);

    //deSerialize the cab
    BasicCab *basicCab;
    boost::iostreams::basic_array_source<char> device(buffer, sizeof(buffer));
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2
            (device);
    boost::archive::binary_iarchive ia(s2);

    ia >> basicCab;

    //attaching the relevant cab to the driver
    driver->setCab(*basicCab);
    bool reciveData = true;
    //recive data
    while (reciveData) {
        socket->reciveData(buffer, sizeof(buffer), client);
        string str = buffer;
        if (str == "close") {
            reciveData = false;
            continue;
        }
        //if there is a new location
        socket->reciveData(buffer, sizeof(buffer), client);
        Node *node;
        boost::iostreams::basic_array_source<char> device(buffer,
                                                          sizeof(buffer));
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3
                (device);
        boost::archive::binary_iarchive ia(s3);
        ia >> node;

        driver->updateCabLocation(*node);
        delete node;
    }

    delete driver;
    delete basicCab;
    delete socket;
    return 0;
}

Driver *parseDriver(string str) {
    int saperatorP, driverId, driverAge, driverExp, vehiclId;
    char driverStatus;
    MartialStatus driverStatusStr;
    int numberOfParameters = 0;

    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == ',') {
            numberOfParameters++;
        }
    }

    //the string should have 4 ','
    if (numberOfParameters != 4) {
        return NULL;
    }

    saperatorP = str.find(",");
    driverId = isValidNumber(str.substr(0, saperatorP));
    if (driverId == -1) {
        return NULL;
    }

    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    driverAge = isValidNumber(str.substr(0, saperatorP));
    if (driverAge == -1) {
        return NULL;
    }

    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    string driverStatusStr1 = str.substr(0, saperatorP);
    if (driverStatusStr1.size() != 1) {
        return NULL;
    }

    driverStatus = driverStatusStr1[0];
    switch (driverStatus) {
        case 'S':
            driverStatusStr = SINGLE;
            break;
        case 'M':
            driverStatusStr = MARRIED;
            break;
        case 'D':
            driverStatusStr = DIVORCED;
            break;
        case 'W':
            driverStatusStr = WIDOWED;
            break;
        default:
            return NULL;
    }

    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    driverExp = isValidNumber(str.substr(0, saperatorP));
    if (driverExp == -1) {
        return NULL;
    }

    str = str.substr(saperatorP + 1);
    vehiclId = isValidNumber(str);
    if (vehiclId == -1) {
        return NULL;
    }

    //creating the driver
    Driver *driver = new Driver(driverId, driverAge, driverStatusStr,
                                driverExp);
    driver->setRequestedCabID(vehiclId);
    return driver;
}

int isValidNumber(string str) {
    //checks if the string is not empty.
    if (str.empty()) {
        return -1;
    }

    //checks if the string is built just from digits.
    for (int i = 0; i < str.size(); ++i) {
        if (!isdigit(str[i])) {
            return -1;
        }
    }

    int number = atoi(str.c_str());

    //if the number < 0
    if (number < 0) {
        return -1;
    }

    return number;
}

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
 */
Driver *parseDriver(string str) throw(exception);

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
    Socket *socket = new Tcp(0,port_num);
    getline(cin, str);

    //initialize the socket
    socket->initialize();
    Driver *driver = parseDriver(str);
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

    //recieving the relevant cab
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

Driver *parseDriver(string str) throw(exception) {
    int saperatorP, driverId, driverAge, driverExp, vehiclId;
    char driverStatus;
    MartialStatus driverStatusStr;
    saperatorP = str.find(",");
    driverId = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if (driverId < 0) {
        throw exception();
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    driverAge = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if (driverAge < 0) {
        throw exception();
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    driverStatus = (str.substr(0, 1))[0];
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
            throw exception();
    }

    str = str.substr(saperatorP + 1);
    if (str[0] == '-') {
        throw exception();
    }
    saperatorP = str.find(",");
    driverExp = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    str = str.substr(saperatorP + 1);
    vehiclId = atoi((str.substr(0)).c_str());
    if (vehiclId < 0) {
        throw exception();
    }
    //creating the driver
    Driver *driver = new Driver(driverId, driverAge, driverStatusStr,
                                driverExp);
    driver->setRequestedCabID(vehiclId);
    return driver;
}

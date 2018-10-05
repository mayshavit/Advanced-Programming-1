#include <cstdlib>
#include "MainFlow.h"
#include "LuxuryCab.h"
#include "sockets/Socket.h"
#include "sockets/Udp.h"
#include "sockets/Tcp.h"
//#include "sockets/Tcp.h"
#include <pthread.h>

//global veriables for thread
int mission = 0;
//a vector of bppls that indicates the thread state
vector<bool> threadBoolVec;

MainFlow::MainFlow() {

}

MainFlow::MainFlow(TaxiCenter t) {
    taxiCenter = &t;
}


void MainFlow::startFlow(const int given_port_num) {
    string str;
    int x, y, numOfObstacles;

    const int port_num = given_port_num;
    Socket *socket = new Tcp(1, port_num);
    socket->initialize();
    mainSocket = socket;

    //creating the grid.
    getline(cin, str);
    string delimiter = " ";
    string xString = str.substr((0, str.find(delimiter)));
    string yString = (str.substr(str.find(delimiter) + 1, str.size() - 1));
    x = atoi(xString.c_str());
    y = atoi(yString.c_str());
    //if x<=0 or y<=0.
    if (!validateGridParameters(x, y)) {
        return;
    }
    Grid grid(x, y);
    graph = &grid;
    getline(cin, str);
    //creating the obstacles.
    numOfObstacles = atoi(str.c_str());
    if (validateNumOfObstacles(numOfObstacles)) {
        if (numOfObstacles > 0) {
            for (int i = 0; i < numOfObstacles; ++i) {
                delimiter = ",";
                getline(cin, str);
                int pointX = atoi((str.substr(0, str.find(delimiter))).c_str());
                int pointY = atoi((str.substr(str.find(delimiter) + 1,
                                              str.size() - 1)).c_str());
                Point p(pointX, pointY);
                Node n(p);
                obstacles.push_back(n);
                graph->getNode(n).setPassed(true);
            }
        }
        //if the number of obstacles is <0.
    } else {
        return;
    }

    //choosing the mission's number from the user.
    char taskNum;
    do {
        getline(cin, str);
        taskNum = str[0];
        switch (taskNum) {
            //cases 1-3: parsing the input, and adding the parsed
            // object - driver / trip / cab to the Taxi Center.
            case '1': {
                getline(cin, str);
                int numOfDrives = atoi(str.c_str());
                recieveDrivers(numOfDrives);
                break;
            }
            case '2': {
                getline(cin, str);
                parseTrip(str);
                TripInformation tripInfo = taxiCenter->getTrips().
                        at(taxiCenter->getTrips().size() - 1);
                stack<Node> nodeStack = calculateATrip(tripInfo, obstacles);
                tripInfo.setNodeStack(nodeStack);
                taxiCenter->setATrip(tripInfo);

                break;
            }
            case '3': {
                getline(cin, str);
                parseVehicle(str);
                break;
            }
                //printing the driver's location by given id.
            case '4': {
                getline(cin, str);
                printDriverLocation(str);
                break;
            }
            case '6': {
                break;
            }
                //close the sockets and the program
            case '7': {
                for (int i = 0; i < taxiCenter->getDrivers().size(); ++i) {
                    socket->sendData("close", taxiCenter->getDrivers().at(i)
                            .getClientNum());
                }
                delete socket;
                break;
            }
                //attaching a trip to the driver, and changing his location
            case '9': {
                taxiCenter->increaseCounter();
                taxiCenter->sendCab();
                //update the bool vector for sending data.
                for (int i = 0; i < threadBoolVec.size(); ++i) {
                    threadBoolVec.at(i) = true;
                }
                break;
            }
                //if the mission number is not 1-7
            default:
                break;
        }
    } while (taskNum != '7');
}


void MainFlow::parseTrip(string str) throw(exception) {
    int saperatorP, tripId, tripXStart, tripYStart, tripXEnd,
            tripYEnd, tripNumOfPass, numOfSec;
    double tripTarrif;

    saperatorP = str.find(",");
    tripId = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if (tripId < 0) {
        throw exception();
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    tripXStart = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if (tripXStart < 0) {
        throw exception();
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    tripYStart = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if (tripYStart < 0) {
        throw exception();
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    tripXEnd = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if (tripXEnd < 0) {
        throw exception();
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    tripYEnd = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if (tripYEnd < 0) {
        throw exception();
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    tripNumOfPass = atoi(str.substr(0,
                                    (str.length() - saperatorP - 1)).c_str());
    if (tripNumOfPass <= 0) {
        throw exception();
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    tripTarrif = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if (tripTarrif < 0) {
        throw exception();
    }
    str = str.substr(saperatorP + 1);
    numOfSec = atof((str.substr(0)).c_str());
    if (numOfSec < 0) {
        throw exception();
    }

    //creating the trip
    TripInformation t(tripId, Node(Point(tripXStart, tripYStart)),
                      Node(Point(tripXEnd, tripYEnd)),
                      tripNumOfPass, tripTarrif, numOfSec);
    //attaching it to the taxi center.
    taxiCenter->addTrip(t);

}

void MainFlow::parseVehicle(string str) throw(exception) {
    int saperatorP, vehicleId, vehicleType;
    Manufacturer vehicleManufacturer;
    Color vehicleColor;
    char vehicleManu, vehicleColorCh;

    saperatorP = str.find(",");
    vehicleId = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if (vehicleId < 0) {
        throw exception();
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    vehicleType = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if ((vehicleType != 1) && (vehicleType != 2)) {
        throw exception();
    }

    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    vehicleManu = (str.substr(0, 1))[0];
    switch (vehicleManu) {
        case 'H':
            vehicleManufacturer = HONDA;
            break;
        case 'S':
            vehicleManufacturer = SUBARO;
            break;
        case 'T':
            vehicleManufacturer = TESLA;
            break;
        case 'F':
            vehicleManufacturer = FIAT;
            break;
        default:
            throw exception();
    }
    str = str.substr(saperatorP + 1);
    vehicleColorCh = (str.substr(0, 1))[0];
    switch (vehicleColorCh) {
        case 'R':
            vehicleColor = RED;
            break;
        case 'B':
            vehicleColor = BLUE;
            break;
        case 'G':
            vehicleColor = GREEN;
            break;
        case 'P':
            vehicleColor = PINK;
            break;
        case 'W':
            vehicleColor = WHITE;
            break;
        default:
            throw exception();
    }

    //creating the vehicle according to the user's choice.
    BasicCab bc;
    if (vehicleType == 1) {
        Cab cab(vehicleId, vehicleManufacturer, vehicleColor);
        bc = cab;
    } else if (vehicleType == 2) {
        LuxuryCab luxCab(vehicleId, vehicleManufacturer, vehicleColor);
        bc = luxCab;
    }
    //attaching it to the taxi center.
    taxiCenter->addCab(bc);
}

void MainFlow::printDriverLocation(string str) throw(exception) {
    int driverIdGet;

    driverIdGet = atoi(str.c_str());
    if (driverIdGet < 0) {
        throw exception();
    }
    //look for the driver in the taxi center.
    Driver d = taxiCenter->findDriverByID(driverIdGet);
    cout << d.getCabInfo().getLocation() << endl;
}

bool MainFlow::validateNumOfObstacles(int numOfObstacles) {
    if (numOfObstacles < 0) {
        return false;
    }
    return true;
}

bool MainFlow::validateGridParameters(int x, int y) {
    if ((x <= 0) || (y <= 0)) {
        return false;
    }
    return true;
}

void MainFlow::recieveDrivers(int numOfDrivers) {

    //reset th vector
    for (int k = 0; k < numOfDrivers; ++k) {
        threadBoolVec.push_back(false);
    }

    //open a thread for each driver
    for (int i = 0; i < numOfDrivers; i++) {
        pthread_t driverThread;

        MainFlow *mainFlowPtr = new MainFlow(4);
        //set a copy of the graph to the driver.
        Graph *g = new Grid(graph->getWidth(), graph->getHeight());
        for (int j = 0; j < obstacles.size(); ++j) {
            graph->getNode(obstacles.at(j)).setPassed(true);
        }
        mainFlowPtr->graph = g;
        mainFlowPtr->taxiCenter = taxiCenter;
        mainFlowPtr->obstacles = obstacles;
        mainFlowPtr->mainSocket = mainSocket;

        //create the thread
        int status = pthread_create(&driverThread, NULL, reciveADriver,
                                    (void *) mainFlowPtr);

        if (status) {
            cout << "coud not open thread" << endl;
        }
    }
}

stack<Node> MainFlow::calculateATrip(TripInformation tripInfo,
                                     vector<Node> obstacles) {
    pthread_t calcThread;

    Grid *grid = new Grid(graph->getWidth(), graph->getHeight());
    int size = obstacles.size();
    if (size > 0) {
        for (int i = 0; i < size; ++i) {
            Node n = obstacles.at(i);
            n.setPassed(true);
            grid->setNode(n);
        }
    }
    tripInfo.setCityGrid(grid);

    TripInformation *tripInformationPtr = &tripInfo;
    //open the thread
    int status = pthread_create(&calcThread, NULL,
                                tripInfo.calculateWayByBFS,
                                (void *) tripInformationPtr);

    if (status) {
        cout << "could not open thread" << endl;
    }

    pthread_join(calcThread, NULL);

    delete (grid);
    return tripInformationPtr->getNodeStack();
}


void *MainFlow::reciveADriver(void *givenMainFlow) {
    MainFlow *mainFlow = reinterpret_cast<MainFlow *>(givenMainFlow);

    Socket *socket = mainFlow->mainSocket;
    TaxiCenter *taxiCenter = mainFlow->taxiCenter;
    Graph *graph = mainFlow->graph;

    int client = socket->connectAClient();

    char buffer[2048];
    //recieving the driver
    socket->reciveData(buffer, sizeof(buffer), client);
    //deSerialize the driver
    Driver *driver;
    boost::iostreams::basic_array_source<char> device(buffer,
                                                      sizeof(buffer));
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(
            device);
    boost::archive::binary_iarchive ia(s);

    ia >> driver;

    //find the cab by requested id and attach it to the driver
    BasicCab cab = taxiCenter->findCabByID(driver->getRequestedCabID());
    driver->setCab(cab);

    Driver serializedDriver = *driver;
    serializedDriver.setGraph(graph);
    serializedDriver.setClientNum(client);
    serializedDriver.setCurrentlyOccupied(false);
    serializedDriver.setReachedToDest(false);
    serializedDriver.setToSend(false);
    serializedDriver.setThreadNum(taxiCenter->getDrivers().size());
   
    //add the driver to the taxi center
    taxiCenter->addDriver(serializedDriver);
    delete driver;

    //serialize the cab
    BasicCab *basicCab;
    basicCab = &cab;
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::
    stream<boost::iostreams::back_insert_device<std::string> > s2(inserter);
    boost::archive::binary_oarchive oa(s2);
    oa << basicCab;
    s2.flush();
    //send the serialized cab to the client
    socket->sendData(serial_str, client);

    int boolPlace = serializedDriver.getThreadNum();
    while (mission != 7) {
        if (threadBoolVec.at(boolPlace) == true) {
            int j = taxiCenter->findDriverPlace(serializedDriver);
            int driversClientNum = taxiCenter->getDrivers().at(j)
                    .getClientNum();
            if (taxiCenter->getDrivers().at(j).isToSend()) {
                socket->sendData("continue", driversClientNum);

                Node node = taxiCenter->getDrivers().at(j).getCabInfo()
                        .getLocation();
                Node *serializedNode = new Node(node.getPoint());
                std::string serial_str;
                boost::iostreams::back_insert_device<std::string> inserter(
                        serial_str);
                boost::iostreams::stream
                        <boost::iostreams::back_insert_device
                                <std::string> > s(inserter);
                boost::archive::binary_oarchive oa(s);
                oa << serializedNode;
                s.flush();

                socket->sendData(serial_str, driversClientNum);

                delete serializedNode;

            }
            //we already passed on the graph - we need a "clean" graph like
            //in the beginning, updated by the given obstacles we've got.
            if (taxiCenter->getDrivers().at(j).isReachedToDest()) {
                taxiCenter->updateDriver(taxiCenter->getDrivers().at(j));

                int location = taxiCenter->findDriverPlace
                        (taxiCenter->getDrivers().at(j));

                //attaching the "clean" graph to all of the drivers.
                graph->resetGraph();
                int numOfObstacles = mainFlow->obstacles.size();
                if (numOfObstacles > 0) {
                    for (int i = 0; i < numOfObstacles; i++) {
                        Node n = mainFlow->obstacles.at(i);
                        n.setPassed(true);
                        graph->setNode(n);
                    }
                }
                taxiCenter->updateGraph(graph, location);
            }
            threadBoolVec.at(boolPlace) = false;
        }
    }


}

void MainFlow::setMainSocket(Socket *socket) {
    mainSocket = socket;
}

Socket *MainFlow::getMainSocket() {
    return mainSocket;
}

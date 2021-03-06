#include <cstdlib>
#include "MainFlow.h"
#include "LuxuryCab.h"
#include "sockets/Socket.h"
#include "sockets/Udp.h"
#include "sockets/Tcp.h"
#include "ThreadPool/ThreadPool.h"
#include <boost/algorithm/string.hpp>
#include <pthread.h>
#include <sstream>
#include "boost/rational.hpp"


//global variables for thread
int mission = 0;
//a vector of bools that indicates the thread state
vector<bool> threadBoolVec;

MainFlow::MainFlow() {

}

MainFlow::MainFlow(TaxiCenter t) {
    taxiCenter = &t;
}


void MainFlow::startFlow(const int given_port_num) {
    string str;
    string delimiter;
    int x, y, numOfObstacles;
    Grid grid;
    ThreadPool pool(5);
    vector<Grid *> gridVec;
    vector<MainFlow *> mainFlowVec;
    bool toAssign = false;

    const int port_num = given_port_num;
    Socket *socket = new Tcp(1, port_num);
    socket->initialize();
    mainSocket = socket;

    

    while (true) {
        bool print = true;
        //creating the grid.
        getline(cin, str);
        boost::trim_right(str);
        boost::trim_left(str);
        if (validateGridParameters(str)) {
            int delimiterPlace = str.find(" ");
            x = atoi(str.substr(0, delimiterPlace).c_str());
            y = atoi(str.substr(delimiterPlace + 1, str.size() - 1).c_str());
            grid = Grid(x, y);
            graph = &grid;
            getline(cin, str);
            //creating the obstacle.
            numOfObstacles = isValidNumber(str);
            if (numOfObstacles != -1) {
                if (numOfObstacles == 0) {
                    print = false;
                } else {
                    for (int i = 0; i < numOfObstacles; ++i) {
                        delimiter = ",";
                        getline(cin, str);
                        if (validateNumberOfParameters(str) == 1) {
                            int pointX = isValidNumber(str.substr(0, str.find
                                    (delimiter)));
                            int pointY = isValidNumber((str.substr(str.find
                                    (delimiter) + 1)));
                            if ((validateNodeParameters(x, y, pointX,
                                                        pointY)) &&
                                (pointX != -1) && (pointY != -1)) {
                                Point p(pointX, pointY);
                                Node n(p);
                                obstacles.push_back(n);
                                graph->getNode(n).setPassed(true);
                                print = false;
                            } else {
                                break;
                            }

                        } else if (validateNumberOfParameters(str) == 0) {
                            print = true;
                            break;
                        }
                    }
                }
            }
        }
        //the parameters were invalid
	//in the original excersize, there was no instruction whether to print
	//"-1" or not, I assumed that in this stagem we should print "-1".
        if (print) {
            cout << "-1" << endl;
        } else {
            break;
        }
    }

    //connecting to GUI
    int guiClient = socket->connectAClient();

    //sending the GUI the width and height parameters
    string string1 = to_string(x) + "\n";
    socket->sendData(string1, guiClient);
    string1 = to_string(y) + "\n";
    socket->sendData(string1, guiClient);

    //sending the GUI the obstacles
    string1 = to_string(numOfObstacles) + "\n";
    socket->sendData(string1, guiClient);
    for (int j = 0; j < numOfObstacles; ++j) {
        string1 = to_string(obstacles.at(j).getNodePx()) + "\n";
        socket->sendData(string1, guiClient);
        string1 = to_string(obstacles.at(j).getNodePy()) + "\n";
        socket->sendData(string1, guiClient);
    }

    int taskNum;
    bool continueMenu = true;
    char buffer[240];
    do {
        //recieving the task number from the GUI
        memset(buffer, 0, sizeof(buffer));
        socket->reciveData(buffer, sizeof(buffer), guiClient);
        taskNum = isValidNumber(buffer);

        while (pool.isOccupied()) {
            //do nothing
        }

        while (toAssign) {
            //if there are calculated stacks of nodes to assign
            if ((!pool.getTripVec().empty())) {
                assignStacksToTripInfos(pool.getTripVec());
                pool.cleanVec();
                toAssign = false;
            }
        }
        if (taskNum != -1) {
            //send the GUI the task number - so it wouldn't print "-1"
            string1 = to_string(taskNum) + "\n";
            
            //choosing the mission's number from the user.
            switch (taskNum) {
                //case 1: connect clients - drivers, to socket .
                case 1: {
		    socket->sendData(string1, guiClient);
                    memset(buffer, 0, sizeof(buffer));
                    socket->reciveData(buffer, sizeof(buffer), guiClient);
                    int numOfDrives;
                    numOfDrives = isValidNumber(buffer);
                    if (numOfDrives != -1) {
                        socket->sendData("1\n", guiClient);
                        recieveDrivers(numOfDrives, gridVec, mainFlowVec);

                        int size = taxiCenter->getDrivers().size();
                        int driverPlace = size + numOfDrives - 1;
                        int expectedSize = size + numOfDrives;

                        //send the GUI the new drivers that were added to the
                        // taxi center
                        while (numOfDrives > 0) {
                            sleep(1);
                            if (taxiCenter->getDrivers().size() ==
                                expectedSize) {
                                Driver driver = taxiCenter->getDrivers().at
                                        (driverPlace);
                                BasicCab cab = driver.getCabInfo();
                                Node node = cab.getLocation();
                                string1 = to_string(driver.getId()) + "\n";
                                socket->sendData(string1, guiClient);
                                socket->sendData(
                                        to_string(node.getNodePx()) + "\n",
                                        guiClient);
                                socket->sendData(
                                        to_string(node.getNodePy()) + "\n",
                                        guiClient);
                                socket->sendData(to_string(cab.getColor())
                                                 + "\n", guiClient);
                                driverPlace--;
                                numOfDrives--;
                            }
                        }
                    } else {
                        //send the GUI a message to print "-1"
                        socket->sendData("-1\n", guiClient);
                    }
                    break;
                }
                    //cases 2-3: parsing the input, and adding the parsed
                    // object - driver / trip / cab to the Taxi Center.
                case 2: {
		    socket->sendData(string1, guiClient);
                    memset(buffer, 0, sizeof(buffer));
                    socket->reciveData(buffer, sizeof(buffer), guiClient);
                    if (parseTrip(x, y, buffer)) {
                        socket->sendData("1\n", guiClient);
                        TripInformation tripInfo = taxiCenter->getTrips().
                                at(taxiCenter->getTrips().size() - 1);
                        Grid *grid = new Grid(graph->getWidth(),
                                              graph->getHeight());
                        int size = obstacles.size();
                        if (size > 0) {
                            for (int i = 0; i < size; ++i) {
                                Node n = obstacles.at(i);
                                n.setPassed(true);
                                grid->setNode(n);
                            }
                        }
                        tripInfo.setCityGrid(grid);

                        //calculate trip by bfs
                        pool.startJob();
                        Job job = Job(tripInfo.calculateWayByBFS,
                                      &tripInfo);
                        pool.addJob(&job);

                        toAssign = true;
                        break;
                    } else {
                        //send the GUI a message to print "-1"
                        socket->sendData("-1\n", guiClient);
                    }
                    break;
                }
                case 3: {
		    socket->sendData(string1, guiClient);
                    memset(buffer, 0, sizeof(buffer));
                    socket->reciveData(buffer, sizeof(buffer), guiClient);
                    if (parseVehicle(buffer) == -1) {
                        socket->sendData("-1\n", guiClient);
                    } else {
                        //send the GUI a message to print "-1"
                        socket->sendData("1\n", guiClient);
                    }
                    break;
                }
                    //case 4: printing the driver's location by given id.
                case 4: {
		    socket->sendData(string1, guiClient);
                    memset(buffer, 0, sizeof(buffer));
                    socket->reciveData(buffer, sizeof(buffer), guiClient);
                    if (printDriverLocation(buffer)) {
                        socket->sendData("1\n", guiClient);
                    } else {
                        socket->sendData("-1\n", guiClient);
                    }
                    break;
                }
                    //case 7: close the sockets and the program
                case 7: {
		    socket->sendData(string1, guiClient);
                    pool.terminate();

                    //close the clients' sockets
                    for (int i = 0; i < taxiCenter->getDrivers().size(); ++i) {
                        socket->sendData("close", taxiCenter->getDrivers().at(i)
                                .getClientNum());
                    }


                    deleteGridsAndMainFlows(gridVec, mainFlowVec);
                    taxiCenter->getCabs().clear();
                    taxiCenter->getDrivers().clear();
                    taxiCenter->getTrips().clear();
                    gridVec.clear();
                    mainFlowVec.clear();

                    delete socket;
                    continueMenu = false;
                    break;
                }
                    //case 9: attaching a trip to the driver, and changing his
                    // location
                case 9: {
		    socket->sendData(string1, guiClient);
                    taxiCenter->increaseCounter();
                    taxiCenter->sendCab();

                    //update the bool vector for sending data.
                    for (int i = 0; i < threadBoolVec.size(); ++i) {
                        threadBoolVec.at(i) = true;
                    }

                    //send the GUI the locations of all drivers.
                    sendDriversLocationToGUI(socket, guiClient);
                    break;
                }
                    //if the mission number is not 1-7
                default:
                    //send the GUI a message to print "-1"
                    socket->sendData("-1\n", guiClient);
                    break;
            }
            //if the task number is invalid
        } else {
            //send the GUI a message to print "-1"
            socket->sendData("-1\n", guiClient);
        }
    } while (continueMenu);
}


bool MainFlow::parseTrip(int gridSizeX, int gridSizeY, string str) {

    int saperatorP, tripId, tripXStart, tripYStart, tripXEnd,
            tripYEnd, tripNumOfPass, numOfSec;
    double tripTarrif;

    str = str.substr(0, str.find('\n'));
    if (validateNumberOfParameters(str) != 7) {
        return false;
    }
    saperatorP = str.find(",");
    tripId = isValidNumber(str.substr(0, saperatorP));

    if (tripId == -1) {
        return false;
    }

    //if there is a trip in the taxi-center with the same id
    if (taxiCenter->isATrip(tripId)) {
        return false;
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    tripXStart = isValidNumber(str.substr(0, saperatorP));
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    tripYStart = isValidNumber(str.substr(0, saperatorP));

    if ((tripXStart == -1) || (tripYStart == -1)) {
        return false;
    }
    if (!validateNodeParameters(gridSizeX, gridSizeY, tripXStart,
                                tripYStart)) {
        return false;
    }

    if (isObstacle(Node(Point(tripXStart, tripYStart)))) {
        return false;
    }

    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    tripXEnd = isValidNumber(str.substr(0, saperatorP));
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    tripYEnd = isValidNumber(str.substr(0, saperatorP));

    if ((tripXEnd == -1) || (tripYEnd == -1)) {
        return false;
    }

    if (!validateNodeParameters(gridSizeX, gridSizeY, tripXEnd, tripYEnd)) {
        return false;
    }

    if (isObstacle(Node(Point(tripXEnd, tripYEnd)))) {
        return false;
    }

    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    tripNumOfPass = isValidNumber(str.substr(0, saperatorP));
    if (tripNumOfPass == -1) {
        return false;
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    tripTarrif = isValidNumber(str.substr(0, saperatorP));
    if (tripTarrif == -1) {
        //check if tarrif is a double number.
        tripTarrif = isDouble(str.substr(0, saperatorP));
        if (tripTarrif == -1) {
            return false;
        }

    }
    str = str.substr(saperatorP + 1);
    numOfSec = isValidNumber(str);
    if (numOfSec <= 0) {
        return false;
    }

    //creating the trip
    TripInformation t(tripId, Node(Point(tripXStart, tripYStart)),
                      Node(Point(tripXEnd, tripYEnd)),
                      tripNumOfPass, tripTarrif, numOfSec);
    //attaching it to the taxi center.
    taxiCenter->addTrip(t);
    return true;

}

int MainFlow::parseVehicle(string str) {

    int saperatorP, vehicleId, vehicleType;
    Manufacturer vehicleManufacturer;
    Color vehicleColor;
    char vehicleManu, vehicleColorCh;

    str = str.substr(0, str.find("\n"));

    if (validateNumberOfParameters(str) != 3) {
        return -1;
    }

    saperatorP = str.find(",");
    vehicleId = isValidNumber(str.substr(0, saperatorP));
    if (vehicleId == -1) {
        return -1;
    }

    if (taxiCenter->isACab(vehicleId)) {
        return -1;
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    vehicleType = isValidNumber(str.substr(0, saperatorP));
    if ((vehicleType != 1) && (vehicleType != 2)) {
        return -1;
    }

    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    if (isChar(str.substr(0, saperatorP))) {
        vehicleManu = str[0];

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
                return -1;
        }
    } else {
        return -1;
    }
    str = str.substr(saperatorP + 1);

    if (isChar(str.substr(0, saperatorP))) {

        vehicleColorCh = str[0];
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
                return -1;
        }
    } else {
        return -1;
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
    return 1;
}

bool MainFlow::printDriverLocation(string str) {
    int driverIdGet;

    driverIdGet = isValidNumber(str);
    Driver d(driverIdGet, 0, MARRIED, 0);

    //if it is a valid number and the requested id is in the taxi-center's
    // drivers.
    if ((driverIdGet != -1) &&
        (taxiCenter->findDriverPlace(d) != -1)) {

        //look for the driver in the taxi center.
        d = taxiCenter->findDriverByID(driverIdGet);
        cout << d.getCabInfo().getLocation() << endl;
        return true;
    } else {
        return false;
    }
}

bool MainFlow::validateGridParameters(string str) {
    int x, y, separator = 0;

    for (int i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            if (str[i] == ' ') {
                separator++;
            } else {
                return false;
            }
        }
    }

    if (separator != 1) {
        return false;
    }

    x = atoi(str.substr(0, str.find(" ")).c_str());
    y = atoi(str.substr(str.find(" ") + 1, str.length() - 1).c_str());
    if ((x <= 0) || (y <= 0)) {
        return false;
    }
    return true;
}

void MainFlow::recieveDrivers(int numOfDrivers, vector<Grid *> gridVec,
                              vector<MainFlow *> mainFlowVec) {

    //reset the vector
    for (int k = 0; k < numOfDrivers; ++k) {
        threadBoolVec.push_back(false);
    }

    //open a thread for each driver
    for (int i = 0; i < numOfDrivers; i++) {
        pthread_t driverThread;

        MainFlow *mainFlowPtr = new MainFlow(4);
        //set a copy of the graph to the driver.
        Grid *grid = new Grid(graph->getWidth(), graph->getHeight());
        Graph *g = grid;
        for (int j = 0; j < obstacles.size(); ++j) {
            graph->getNode(obstacles.at(j)).setPassed(true);
        }
        mainFlowPtr->graph = g;
        mainFlowPtr->taxiCenter = taxiCenter;
        mainFlowPtr->obstacles = obstacles;
        mainFlowPtr->mainSocket = mainSocket;

        gridVec.push_back(grid);
        mainFlowVec.push_back(mainFlowPtr);

        //create the thread
        int status = pthread_create(&driverThread, NULL, reciveADriver,
                                    (void *) mainFlowPtr);


        if (status) {
            cout << "coud not open thread" << endl;
        }
    }
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

bool MainFlow::validateNodeParameters(int gridSizeX, int gridSizeY,
                                      int nodeSizeX, int nodeSizeY) {

    if ((nodeSizeX < 0) || (nodeSizeY < 0) || (nodeSizeX >= gridSizeX) ||
        (nodeSizeY >= gridSizeY)) {
        return false;
    }
    return true;

}

int MainFlow::validateNumberOfParameters(string str) {
    int numOfParameters = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == ',') {
            numOfParameters++;
        }
    }

    return numOfParameters;
}

int MainFlow::isValidNumber(string str) {
    str = str.substr(0, str.find('\n'));
    if (str.empty()) {
        return -1;
    }
    //check if the string is a digit
    for (int i = 0; i < str.size(); ++i) {
        if (!isdigit(str[i])) {
            return -1;
        }
    }

    int number = atoi(str.c_str());
    if (number < 0) {
        return -1;
    }
    return number;
}

double MainFlow::isDouble(string str) {
    int numOfDots = 0;
    if (str.size() == 0) {
        return -1;
    }
    if (str[0] == '.') {
        return -1;
    }
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '.') {
            numOfDots++;
        }
    }

    if (numOfDots != 1) {
        return -1;
    }


    double num1 = isValidNumber(str.substr(0, str.find(".")));
    double num2 = isValidNumber(str.substr(str.find(".") + 1));

    if (num1 == -1) {
        return -1;
    }
    if (num2 == -1) {
        return -1;
    }

    num1 = atof(str.c_str());
    return num1;
}

bool MainFlow::isChar(string str) {
    if (str.size() != 1) {
        return false;
    }
    if (!isalpha(str[0])) {
        return false;
    }
    return true;
}

void MainFlow::assignStacksToTripInfos(vector<TripInformation> tripVec) {
    int taxiCenterTripsSize = taxiCenter->getTrips().size();
    for (int j = taxiCenterTripsSize - 1; j >= 0; --j) {
        TripInformation tripInfo = taxiCenter->getTrips().at(j);
        for (int i = 0; i < tripVec.size(); ++i) {
            if (tripVec.at(i).getId() == tripInfo.getId()) {
                vector<Node> nodeVec = tripVec.at(i).getNodeVec();
                if (nodeVec.empty()) {
                    taxiCenter->removeTrip(tripInfo);
                } else {
                    tripInfo.setNodeVec(nodeVec);
                    taxiCenter->setATrip(tripInfo);
                }
                continue;
            }
        }
    }


}

void MainFlow::deleteGridsAndMainFlows(vector<Grid *> gridVec,
                                       vector<MainFlow *> mainFlowVec) {
    int gridsSize = gridVec.size();
    int mainFlowSize = mainFlowVec.size();

    for (int i = 0; i < gridsSize; ++i) {
        delete gridVec[i];
    }

    for (int j = 0; j < mainFlowSize; ++j) {
        delete mainFlowVec[j];
    }


}

void MainFlow::sendDriversLocationToGUI(Socket *socket, int guiClient) {

    int size = taxiCenter->getDrivers().size();
    Driver driver;
    BasicCab basicCab;
    for (int j = 0; j < size; ++j) {
        driver = taxiCenter->getDrivers().at(j);
        basicCab = driver.getCabInfo();
        socket->sendData(to_string(driver.getId()) + "\n", guiClient);
        socket->sendData(to_string(basicCab.getLocation().getNodePx()) + "\n",
                         guiClient);
        socket->sendData(to_string(basicCab.getLocation().getNodePy()) + "\n",
                         guiClient);
    }
}

bool MainFlow::isObstacle(Node node) {

    for (int i = 0; i < obstacles.size(); ++i) {
        if (node.isEqual(obstacles.at(i))) {
            return true;
        }
    }
    return false;
}

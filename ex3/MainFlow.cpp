#include <cstdlib>
#include "MainFlow.h"
#include "LuxuryCab.h"

MainFlow::MainFlow() {

}

MainFlow::MainFlow(TaxiCenter t) {
    taxiCenter = t;
}


void MainFlow::startFlow() {
    string str;
    int x, y, numOfObstacles;
    vector<Node> obstacles;

    //creating the grid.
    getline(cin, str);
    x = atoi((str.substr(0, 1)).c_str());
    y = atoi((str.substr(str.find(" ") + 1, 1)).c_str());
    //if x<=0 or y<=0.
    if (!validateGridParameters(x,y)){
        return;
    }
    Grid grid(x, y);
    graph = &grid;
    getline(cin, str);
    //creating the obstacles.
    numOfObstacles = atoi(str.c_str());
    if (validateNumOfObstacles(numOfObstacles)) {

        if (numOfObstacles > 0) {
            Node trashNode(Point(-1, -1));
            trashNode.setValid(false);
            trashNode.setPassed(true);
            for (int i = 0; i < numOfObstacles; ++i) {
                getline(cin, str);

                Point p(atoi((str.substr(0, 1)).c_str()),
                        atoi((str.substr((str.find(",") + 1), 1)).c_str()));
                Node n(p);
                obstacles.push_back(n);
                graph->setSource(n, trashNode);
                graph->getSource(n).setPassed(true);
            }
        }
        //if the number of obstacles is <0.
    } else{
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
                getline(cin,str);
                parseDriver(str);
                break;
            }
            case '2': {
                getline(cin,str);
                parseTrip(str);
                break;
            }
            case '3': {
                getline(cin,str);
                parseVehicle(str);
                break;
            }
            //printing the driver's location by given id.
            case '4': {
                getline(cin,str);
                printDriverLocation(str);
                break;
            }
            //attaching a trip to the driver, and changing his location.
            case '6': {
                taxiCenter.answerCall();

                //we already passed on the graph - we need a "clean" graph like
                //in the beginning, updated by the given obstacles we've got.
                Grid grid2 (x,y);
                graph=&grid2;
                if (numOfObstacles>0) {
                    Node trashNode(Point(-1, -1));
                    trashNode.setValid(false);
                    trashNode.setPassed(true);
                    for (int i = 0; i < numOfObstacles; ++i) {
                        Node n = obstacles.at(i);
                        graph->setSource(n, trashNode);
                        graph->getSource(n).setPassed(true);
                    }
                }
                //attaching the "clean" graph to all of the drivers.
                taxiCenter.updateGraph(graph);
                break;
            }
            case '7': {
                break;
            }
            //if the mission number is not 1-7
            default:
                break;
        }
    } while (taskNum != '7');
}

void MainFlow::parseDriver(string str) throw(exception) {
    int saperatorP, driverId, driverAge, driverExp, vehiclId;
    char driverStatus;
    MartialStatus driverStatusStr;
    saperatorP = str.find(",");
    driverId = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if (driverId<0){
        throw exception();
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    driverAge = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if (driverAge<0){
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
    if (str[0]=='-'){
        throw exception();
    }
    saperatorP = str.find(",");
    driverExp = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    str = str.substr(saperatorP + 1);
    vehiclId = atoi((str.substr(0)).c_str());
    if (vehiclId<0){
        throw  exception();
    }
    //creating the driver
    Driver driver(driverId, driverAge, driverStatusStr, driverExp);
    //attacing the driver the relevant cab
    BasicCab cab = taxiCenter.findCabByID(vehiclId);
    driver.setCab(cab);
    driver.setGraph(graph);
    //attaching the driver to the taxi center.
    taxiCenter.addDriver(driver);
}

void MainFlow::parseTrip(string str) throw(exception) {
    int saperatorP, tripId, tripXStart, tripYStart, tripXEnd,
            tripYEnd, tripNumOfPass;
    double tripTarrif;

    saperatorP = str.find(",");
    tripId = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if (tripId<0){
        throw exception();
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    tripXStart = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if (tripXStart<0){
        throw exception();
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    tripYStart = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if (tripYStart<0){
        throw exception();
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    tripXEnd = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if (tripXEnd<0){
        throw exception();
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    tripYEnd = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if (tripYEnd<0){
        throw exception();
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    tripNumOfPass = atoi(str.substr(0,
                                    (str.length() - saperatorP - 1)).c_str());
    if (tripNumOfPass<=0){
        throw exception();
    }
    str = str.substr(saperatorP + 1);
    tripTarrif = atof((str.substr(0)).c_str());
    if (tripTarrif<0){
        throw exception();
    }
    //creating the trip
    TripInformation t(tripId, Node(Point(tripXStart, tripYStart)),
                      Node(Point(tripXEnd, tripYEnd)),
                      tripNumOfPass, tripTarrif);
    //attaching it to the taxi center.
    taxiCenter.addTrip(t);
}

void MainFlow::parseVehicle(string str) throw(exception) {
    int saperatorP, vehicleId, vehicleType;
    Manufacturer vehicleManufacturer;
    Color vehicleColor;
    char vehicleManu, vehicleColorCh;

    saperatorP = str.find(",");
    vehicleId = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if (vehicleId<0){
        throw exception();
    }
    str = str.substr(saperatorP + 1);
    saperatorP = str.find(",");
    vehicleType = atoi(str.substr(0, (str.length() - saperatorP - 1)).c_str());
    if ((vehicleType!=1)&&(vehicleType!=2)){
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
    taxiCenter.addCab(bc);
}

void MainFlow::printDriverLocation(string str) throw(exception) {
    int driverIdGet;

    driverIdGet = atoi(str.c_str());
    if (driverIdGet<0){
        throw exception();
    }
    //look for the driver in the taxi center.
    Driver d = taxiCenter.findDriverByID(driverIdGet);
    cout << d.getCabInfo().getLocation() << endl;
}

bool MainFlow::validateNumOfObstacles (int numOfObstacles) {
    if (numOfObstacles<0){
        return false;
    }
    return true;
}

bool MainFlow::validateGridParameters(int x, int y) {
    if ((x<=0) || (y<=0)){
        return false;
    }
    return true;
}

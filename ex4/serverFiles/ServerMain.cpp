#include <iostream>
#include "sockets/Udp.h"
#include "TaxiCenter.h"
#include "MainFlow.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
    //get the port number from the command line.
    const int port_num = atoi(argv[1]);
    TaxiCenter taxiCenter(4);
    MainFlow mainFlow(taxiCenter);
    mainFlow.startFlow(port_num);
    return 0;
}
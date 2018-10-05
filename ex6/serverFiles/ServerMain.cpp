#include <iostream>
#include "MainFlow.h"
#include <unistd.h>

/*
 * The Server main function.
 * This function is responsible for running the program
 */
int main(int argc, char *argv[]) {
    //get the port number from the command line.
    const int port_num = atoi(argv[1]);

    //run the program
    TaxiCenter taxiCenter(4);
    MainFlow mainFlow(taxiCenter);
    mainFlow.startFlow(port_num);
    return 0;
}
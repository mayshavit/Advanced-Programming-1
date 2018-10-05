#include <iostream>
#include <gtest/gtest.h>
#include <queue>
#include "Grid.h"
#include "BFS.h"
#include "TaxiCenter.h"
#include "MainFlow.h"

using namespace std;
/**
 * The main function.
 * Responsible for running the program.
 */
int main(int argc, char* argv []) {
    //Running the tests
    testing::InitGoogleTest(&argc,argv);
    RUN_ALL_TESTS();
    return 0;
}

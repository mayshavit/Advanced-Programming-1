#include <iostream>
#include <gtest/gtest.h>

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

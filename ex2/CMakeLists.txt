cmake_minimum_required(VERSION 3.3)
project(ex2testsAdvanced)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(SOURCE_FILES main.cpp Point.cpp Point.h Node.cpp Node.h Grid.cpp Grid.h Graph.cpp
        Graph.h Driver.cpp Driver.h TripInformation.cpp TripInformation.h Cab.cpp
        Cab.h LuxuryCab.cpp LuxuryCabTest.h Passenger.cpp Passenger.h TaxiCenter.cpp
        TaxiCenter.h MainFlow.cpp MainFlow.h LocationListener.cpp LocationListener.h
        test/PointTest.cpp BFS.cpp BFS.h test/DriverTest.cpp test/CabTest.cpp
        test/NodeTest.cpp test/LuxuryCabTest.cpp test/PassengerTest.cpp test/GridTest.cpp
        test/TripInformationTest.cpp test/TaxiCenterTest.cpp test/LocationListenerTest.cpp
        test/MainFlowTest.cpp test/BFSTest.cpp)
add_executable(ex2testsAdvanced ${SOURCE_FILES})
target_link_libraries(ex2testsAdvanced gtest gtest_main)


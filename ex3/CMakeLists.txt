cmake_minimum_required(VERSION 3.6)
project(ex3)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(SOURCE_FILES main.cpp Point.cpp Point.h
        Node.cpp Node.h Grid.cpp Grid.h Graph.cpp Graph.h Driver.cpp Driver.h
        TripInformation.cpp TripInformation.h Cab.cpp Cab.h LuxuryCab.cpp
        LuxuryCab.h Passenger.cpp Passenger.h TaxiCenter.cpp TaxiCenter.h
        MainFlow.h BFS.cpp BFS.h test/BFSTest.cpp
        test/BasicCabTest.cpp test/DriverTest.cpp test/GridTest.cpp
        test/MainFlowTest.cpp test/NodeTest.cpp test/PassengerTest.cpp
        test/PointTest.cpp test/TaxiCenterTest.cpp 
        test/TripInformationTest.cpp
        BasicCab.h BasicCab.cpp MainFlow.cpp)
add_executable(ex3 ${SOURCE_FILES})
target_link_libraries(ex3 gtest gtest_main)

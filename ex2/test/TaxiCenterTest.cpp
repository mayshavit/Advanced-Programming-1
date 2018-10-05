
#include <gtest/gtest.h>
#include "../TaxiCenter.h"

/*
 * Test for the TaxiCenter Class.
 */
namespace {
    class TaxiCenterTest : public testing::Test {
    public:
        TaxiCenter obj;

        TaxiCenterTest() {
            obj;
        }

    };
}

/*
 * Test that checks the list of drives.
 * By default, when we create a TaxiCenter instance, the size of the drivers' list
 * should be 0. When we add one driver - it should be 1. Then, when we remove the
 * same driver - it should be 0 again.
 */
TEST_F(TaxiCenterTest, driversTest) {
    TaxiCenter t(4);
    Driver d(2, 3, SINGLE, 0);
    int size1 = t.getDrivers().size();
    EXPECT_EQ(size1, 0);
    t.addDriver(d);
    int size2 = t.getDrivers().size();
    EXPECT_FALSE(size1 == size2);
    t.removeDriver(d);
    int size3 = t.getDrivers().size();
    EXPECT_FALSE(size3 == size2);
}

/*
 * Test that checks the list of cabs.
 * By default, when we create a TaxiCenter instance, the size of the cabs' list
 * should be 0. When we add one cab - it should be 1. Then, when we remove the
 * same cab - it should be 0 again.
 */
TEST_F(TaxiCenterTest, cabsTest) {
    TaxiCenter t(4);
    Cab c(1, 0, TESLA, BLUE, 2, 0);
    int size1 = t.getCabs().size();
    EXPECT_EQ(size1, 0);
    t.addCab(c);
    int size2 = t.getCabs().size();
    EXPECT_FALSE(size1 == size2);
    t.removeCab(c);
    int size3 = t.getCabs().size();
    EXPECT_FALSE(size2 == size3);
}

/*
 * Test that checks the list of tripInformations.
 * By default, when we create a TaxiCenter instance, the size of the trips' list
 * should be 0. When we add one tripInformation - it should be 1. Then, when we
 * remove the same trip - it should be 0 again.
 */
TEST_F(TaxiCenterTest, tripsTest) {
    TaxiCenter t(3);
    TripInformation ti(1, Point(0, 0), Point(1, 1), 3, 2.3);
    int size1 = t.getTrips().size();
    EXPECT_EQ(size1, 0);
    t.addTrip(ti);
    int size2 = t.getTrips().size();
    EXPECT_FALSE(size1 == size2);
    t.removeTrip(ti);
    int size3 = t.getTrips().size();
    EXPECT_FALSE(size2 == size3);
}

/*
 * Test that checks the locations.
 * By default, when we create a TaxiCenter instance, the size of the locations' map
 * should be 0. When we add one location - it should be 1. then, when we remove the
 * same location - it should be 0 again.
 */
TEST_F(TaxiCenterTest, loactionTest) {
    TaxiCenter t(3);
    Driver d(3, 4, SINGLE, 5);
    LocationListener ls(d);
    int size1 = t.getLocations().size();
    EXPECT_EQ(size1, 0);
    t.addLocation(ls);
    int size2 = t.getLocations().size();
    EXPECT_EQ(size2, 1);
    t.removeLocation(d);
    int size3 = t.getLocations().size();
    EXPECT_EQ(size3, 0);
}

/*
 * Test that check the answeCallandSendCab function.
 * The answerCall function should check if there is a driver that can take the
 * trip,if there is such driver, the function returns true.
 * Then, if there is a available driver, we call the sendCab function,
 * where we check who is the closest driver, add a new trip to the tripInformation list,
 * and connect the passengers to the driver.
 */
TEST_F(TaxiCenterTest, answeCallandSendCabTest) {
    TaxiCenter t(3);
    Driver d(3, 4, SINGLE, 5);
    Point point(2, 3);
    Cab c(2, 4, HONDA, GREEN, 4, 5);
    c.setLoaction(point);
    d.setCab(c);
    //there are no drivers nor trip.
    EXPECT_EQ (t.getDrivers().size(), 0);
    EXPECT_EQ(t.getTrips().size(), 0);
    //we add a new available driver
    t.addDriver(d);
    LocationListener ls(d);
    t.addLocation(ls);
    //supposed to be only one driver who is not in a trip, so:
    EXPECT_EQ(t.getDrivers().size(), 1);
    Passenger p(Point(3, 4), Point(5, 6));
    //there is an available driver who is not occupied.
    EXPECT_TRUE(t.answerCall(p));
    //there are no trips yet
    EXPECT_EQ(t.getTrips().size(), 0);
    //now we supposed to send a cab, so we need to create new tripInformation,
    // so the size of trips should be 1.
    t.sendCab(p);
    EXPECT_EQ(t.getTrips().size(), 1);
    //we expect the right passenger was addwd successfully to the driver.
    Driver d2 = t.getDrivers().front();
    Passenger p2 = d2.getCurrentPassengers().front();
    EXPECT_TRUE(p.isEqual(p2));
}

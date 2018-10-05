
#include <gtest/gtest.h>
#include "../TripInformation.h"

/*
 * Test for the TripInformation class.
 */
namespace {
    class TripInformationTest : public testing::Test {
    public:
        TripInformation obj;

        TripInformationTest() {
            obj;
        }
    };
}

/*
 * Test that checks the id update.
 */
TEST_F(TripInformationTest, idTest) {
    TripInformation t(2, Point(0, 0), Point(1, 0), 1, 0);
    EXPECT_EQ(t.getId(), 2);
}

/*
 * Test that checks the start point update.
 */
TEST_F(TripInformationTest, startPointTest) {
    Point p1(0, 0);
    Point p2(1, 0);
    TripInformation t(2, p1, p2, 1, 0);
    EXPECT_TRUE(p1.isEqual(t.getStartPoint()));
}

/*
 * Test that checks the end point update.
 */
TEST_F(TripInformationTest, endPointTest) {
    Point p1(0, 0);
    Point p2(1, 0);
    TripInformation t(2, Point(0, 0), Point(1, 0), 1, 0);
    EXPECT_TRUE(p2.isEqual(t.getEndPoint()));
}

/*
 * Test that checks the passenger number update.
 */
TEST_F(TripInformationTest, passengersNumTest) {
    TripInformation t(2, Point(0, 0), Point(1, 0), 5, 0);
    EXPECT_EQ(t.getPassengersNum(), 5);
}

/*
 * Test that checks the tarrif update.
 */
TEST_F(TripInformationTest, tarrifTest) {
    TripInformation t(2, Point(0, 0), Point(1, 0), 1, 33.3);
    EXPECT_EQ(t.getTarrif(), 33.3);
}

/*
 * Test that checks the total meters update.
 */
TEST_F(TripInformationTest, totalMetersTest) {
    TripInformation t(2, Point(0, 0), Point(1, 0), 1, 3);
    EXPECT_EQ(t.getTotalMeters(), 0);
    t.updateTotalMeters(22);
    EXPECT_EQ(t.getTotalMeters(), 22);
}

/*
 * Test that checks the driver update.
 */
TEST_F(TripInformationTest, driverTest) {
    TripInformation t(2, Point(0, 0), Point(1, 0), 1, 3);
    Driver d(2, 10, SINGLE, 3);
    t.setDriver(d);
    EXPECT_TRUE(d.isEqual(t.getDriver()));
}

/*
 * Test that checks the updateDriverSatisfactionAndCostumers function.
 */
TEST_F(TripInformationTest, satAndCostTest) {
    Driver d(2, 10, SINGLE, 3);
    TripInformation t(2, Point(0, 0), Point(3, 5), 1, 3);
    t.setDriver(d);
    Driver d2 = t.getDriver();
    int satisfaction = d2.getAvgSatisfaction();
    int costumers = d2.getNumOfCostumers();
    t.updateDriverSatisfactionAndCostumers();
    /*we called in the updateDriverSatisfactionAndCostumers to the
    driver's 2 function: updateSatisfaction and uptadeCostumers.
    so, the members of the Driver - aveSaticfaction and numOfCostumers
    should not be the same as satisfaction and costumers.*/
    EXPECT_FALSE(satisfaction == t.getDriver().getAvgSatisfaction());
    EXPECT_FALSE(costumers == t.getDriver().getNumOfCostumers());


}

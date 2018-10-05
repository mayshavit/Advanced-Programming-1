
#include <gtest/gtest.h>
#include "../Cab.h"

/*
 * tests for Cab Class
 */

namespace {
    class CabTest : public testing::Test {
    public:
        Cab obj;

        CabTest() {
            obj;
        }
    };
}

/*
 * Test that checks the Manufacturer update.
 */
TEST_F(CabTest, ManufacturerTest) {
    Cab c(0, 0, TESLA, BLUE, 0, 0);
    EXPECT_EQ(TESLA, c.getCarKind());
}

/*
 * Test that checks the color update.
 */
TEST_F(CabTest, ColorTest) {
    Cab c(0, 0, HONDA, BLUE, 0, 0);
    EXPECT_EQ(BLUE, c.getColor());

}

/*
 * Test that checks the id update.
 */
TEST_F(CabTest, idTest) {
    Cab c(2, 0, HONDA, BLUE, 0, 0);
    EXPECT_EQ(c.getId(), 2);
}

/*
 * Test that checks the tarrif update.
 */
TEST_F(CabTest, tarrifTest) {
    Cab c(0, 0, HONDA, BLUE, 2, 0);
    EXPECT_EQ(c.getTarrif(), 2);
}

/*
 * Test that check the speed update.
 */
TEST_F(CabTest, speedTest) {
    Cab c(0, 0, HONDA, BLUE, 0, 2);
    EXPECT_EQ(c.getSpeed(), 2);
}

/*
 * Test that checks the meters update.
 */
TEST_F(CabTest, metersTest) {
    Cab c(0, 2, HONDA, BLUE, 0, 0);
    EXPECT_EQ(c.getTotalMeters(), 2);
    c.updateTotalMeters(5);
    EXPECT_EQ(c.getTotalMeters(), 4);

}

/*
 * Test that checks the equality of two cars update.
 */
TEST_F (CabTest, isEqualTest) {
    Cab c1(1, 2, HONDA, GREEN, 3, 4);
    Cab c2(1, 2, HONDA, GREEN, 3, 4);
    EXPECT_TRUE(c1.isEqual(c2));
}

/*
 * Test that checks the cab location update.
 */
TEST_F(CabTest, locationTest) {
    Cab c(1, 2, HONDA, GREEN, 3, 4);
    Point loaction(3, 3);
    c.setLoaction(loaction);
    EXPECT_TRUE(loaction.isEqual(c.getLoaction()));
}

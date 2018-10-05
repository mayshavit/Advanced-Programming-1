
#include <gtest/gtest.h>
#include "../LocationListener.h"
/*
 * Test for the LocationListener class.
 */

namespace {
    class LocationListenerTest : public testing::Test {
    public:
        LocationListener obj;

        LocationListenerTest() {
            obj;
        }

    };
}

/*
 * Test that checks if the driver was connected to the listener successfully.
 */
TEST_F(LocationListenerTest, driverTest) {
    Driver d(2, 3, SINGLE, 7);
    LocationListener ls(d);
    EXPECT_TRUE(d.isEqual(ls.getDriver()));
}

/*
 * Test that checks the driver location update.
 */
TEST_F(LocationListenerTest, updateTest) {
    Driver d(2, 3, MARRIED, 5);
    Point p(0, 0);
    LocationListener ls(d);
    ls.updateDriversLocation(p);
    EXPECT_TRUE(p.isEqual(ls.getDriver().getCabInfo().getLoaction()));
}

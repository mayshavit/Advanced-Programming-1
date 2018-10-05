
#include <gtest/gtest.h>
#include "../LuxuryCabTest.h"

/*
 * Test for the LuxuryCab class.
 */

namespace {
    class LuxuryCabTest : public testing::Test {
    public:
        LuxuryCab obj;

        LuxuryCabTest() {
            obj;
        }
    };
}

/*
 * Test that check the speed update - should be twice as fast from the base cab.
 */
TEST_F(LuxuryCabTest, speedTest) {
    LuxuryCab lcab(0, 0, HONDA, GREEN, 0, 0);
    int x1 = lcab.getSpeed();
    lcab.updateSpeed();
    int x2 = lcab.getSpeed();
    EXPECT_EQ(x1 * 2, x2);
}

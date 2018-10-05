
#include <gtest/gtest.h>
#include "../MainFlow.h"

/*
 * Test for the MainFlow class.
 */

namespace {
    class MainFlowTest : public testing::Test {
    public:
        MainFlow obj;

        MainFlowTest() {
            obj;
        }
    };
}

/*
 * Test that checks the parse input update.
 * we don't know yet what is the right/wrong input for our program, so for now, we *assume*
 * that we got wrong input. in that case, the parse input function should throw an exception.
 */
TEST_F(MainFlowTest, parseInputTest) {
    string s = "wrong_input";
    MainFlow mf(3);
    EXPECT_ANY_THROW(mf.parseInput(s));
}

/*
 * Test that checks the cab creation.
 * Again, we don't know yet what is the right/wrong input, so we *assume* we got right input.
 * In that case, the isCreated boolean is initialized first, when we create a MainFlow
 * instance, to false. If the input is good - the parseInput function should not throw an
 * exception. We build our program so that in that case, it will call directly to the creation
 * function. If the creation succeeded - the isCreated boolean should be now true.
 *
 */
TEST_F (MainFlowTest, creationTest) {
    string s = "good_input";
    MainFlow mf(4);
    EXPECT_FALSE(mf.isCreated());
    EXPECT_NO_THROW(mf.parseInput(s));
    EXPECT_TRUE(mf.isCreated());
}

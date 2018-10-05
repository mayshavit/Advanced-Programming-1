//
// Created by may on 29/11/16.
//

#ifndef EX1_MAINFLOW_H
#define EX1_MAINFLOW_H


#include "TaxiCenter.h"

class MainFlow {
private:
    TaxiCenter taxiCenter;
    Grid grid;
    bool created;
public:
    /*
     * The MainFlow constructor.
     */
    MainFlow();

    /*
     * The MainFlow cinstructor.
     * Gets a x.
     */
    MainFlow(int x);

    /*
     * We don't know what input is correct.
     * when we call the parseInput function, if is a good input - we call from it to the
     * creation function, and sends it the parsed strings.
     * It throws exception if the input wasn't good.
     */
    void parseInput(string s) throw(exception);

    /*
     * The creation function translates the many string to integers like int, double etc., and
     * creates the objects. All of them are stored in the grid and in the taxi-center, so the
     * creation function creates the 2 members. Afterwards, the startflow function uses the
     * members. So after the creation, grid and taxiCenter should hold a value.
     * Returns true if the objects were created.
     *
     */


    void creation(string s);

    /*
     * This function supposed to run the program after all of the elements were created.
     */
    void startFlow();

    /*
     * Function that returns the value of the created member.
     */
    bool isCreated() const;

};


#endif

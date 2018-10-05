//
// Created by eliyagvili on 18/11/16.
//

#ifndef EX1_POINT_H
#define EX1_POINT_H

#include <array>
#include <iostream>

using namespace std;

/*
 * The Point class.
 * The class represents a point on the axis.
 */
class Point {
private:
    int x;
    int y;
public:
    /*
     * The Point constructor.
     */
    Point();

    /*
     * The Point constructor.
     * Receives a value and b value.
     */
    Point(int a, int b);

    /*
     * getX function, return the x value.
     */
    int getX();

    /*
     * getY function, return the y value.
     */
    int getY();

    /*
     * isEqual function, gets a Point and return true if the x values and the y values
     * are equal to the values of our point.
     */
    bool isEqual(Point p);

    /*
     * The printing function, this function prints the point.
     */
    friend ostream &operator<<(ostream &output, const Point &p);
};


#endif //EX1_POINT_H

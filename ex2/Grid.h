//
// Created by eliyagvili on 23/11/16.
//

#ifndef EX1_MATRIX_H
#define EX1_MATRIX_H


#include "Node.h"
#include "Graph.h"

/*
 * Grid class implements the Graph functions.
 */
class Grid : public Graph {
private:
    Node grid[10][10];
    int sizeX;
    int sizeY;

public:
    /*
     * The Grid constructor.
     */
    Grid();

    /*
     * The Grid constructor, get the grid width and height.
     */
    Grid(int width, int height);

    /*
     * setSource function that get 2 Nodes.
     * set the secound to be the source of the first.
     */
    void setSource(Node node, Node sourceNode);

    /*
     * getSource function that get node ant return its source node.
     */
    Node getSource(Node node);

    /*
     * validateNeighbors function that get node and validate its nieghbors.
     */
    void validateNeighbors(Node node);

    /*
    * Function that returns the sizex.
    */
    int getWidth();

    /*
     * Function that returns the sizey.
     */
    int getHeight();

    /*
     * Function that returns true if the two grids are equal, else false.
     */
    bool isEqual(Grid g);
};


#endif

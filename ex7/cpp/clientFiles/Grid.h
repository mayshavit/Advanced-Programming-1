#ifndef EX1_MATRIX_H
#define EX1_MATRIX_H


#include "Graph.h"
#include <iostream>

#include <boost/serialization/export.hpp>


/*
 * Grid class implements the Graph functions.
 */
class Grid : public Graph {
private:
    vector<vector<Node> > grid;
    int sizeX;
    int sizeY;

public:
    /*
     * The Grid constructor.
     */
    Grid();

    /*
     * The Grid destructor.
     */
    ~Grid();

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
    Node getNode(Node node);

    /*
     * The stNde function.
     * This function sets the given node to its location in the grid
     */
    void setNode(Node node);

    /*
     * validateNeighbors function that get node and validate its neighbors.
     */
    void validateNeighbors(Node node);

    /*
    * Function that returns the sizeX.
    */
    int getWidth();

    /*
     * Function that returns the sizeY.
     */
    int getHeight();

    /*
     * Function that returns true if the two grids are equal, else false.
     */
    bool isEqual(Grid g);


    /*
     * The resetGraph function.
     * This function resets the graph, so every node is not passed.
     */
    void resetGraph();
};


#endif

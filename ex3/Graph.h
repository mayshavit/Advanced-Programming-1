#ifndef EX1_GRAPH_H
#define EX1_GRAPH_H


#include "Node.h"

/*
 * The Graph class.
 * This is an abstract class with abstruct methodes, (like interface).
 * It makes the program more generic in order that we could use it with
 * every Node.
 */
class Graph {

public:
    /*
     * setSource function that get 2 Nodes.
     * we implement this function in its dirived class.
     */
    virtual void setSource(Node node, Node sourceNode) = 0;

    /*
     * getSource function that get node.
     * we implement this function in its dirived class.
     */
    virtual Node getSource(Node node) = 0;

    /*
     * validateNeighbors function that get node and validate its neighbors.
     * we implement this function in its dirived class.
     */
    virtual void validateNeighbors(Node node) = 0;
};


#endif //EX1_GRAPH_H

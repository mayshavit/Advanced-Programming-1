#ifndef EX1_GRAPH_H
#define EX1_GRAPH_H


#include "Node.h"

#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

/*
 * The Graph class.
 * This is an abstract class with abstruct methods, (like interface).
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
    virtual Node getNode(Node node) = 0;

    /*
     * The setNode function.
     * we implement this function in its derived class.
     */
    virtual void setNode(Node node) = 0;

    /*
     * validateNeighbors function that get node and validate its neighbors.
     * we implement this function in its dirived class.
     */
    virtual void validateNeighbors(Node node) = 0;

    /*
     * The restesGraph function.
     * we implement this function in its derived class.
     */
    virtual void resetGraph() = 0;

    /*
     * Function that returns the width.
     * we implement this function in the derived class.
     */
    virtual int getWidth() = 0;

    /*
     * Function that returns the height.
     * we implement this function in the derived class.
     */
    virtual int getHeight() = 0;
};


#endif //EX1_GRAPH_H

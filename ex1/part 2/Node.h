#ifndef EX1_NODE_H
#define EX1_NODE_H


#include <vector>
#include "Point.h"

/*
 * The Node class.
 * this class represents a Node.
 */
class Node {
private:
    Point point;
    bool passed;
    Node * neighbors[4];
    int numOfNeighbors;
    bool validNode;
public:
    /*
     * the Node constructor.
     */
    Node();

    /*
     * the Node constructor, get Point and create node.
     */
    Node(Point p);

    /*
     * the Node destructor.
     */
    ~Node();

    /*
     * getPoint function, return the point.
     */
    Point getPoint();

    /*
     * getPassed function, return passed.
     */
    bool getPassed();

    /*
     * setPassed function, set the passed to the value given.
     */
    void setPassed(bool psd);

    /*
     * getNodePx function return the x value of the point.
     */
    int getNodePx();

    /*
     * getNodePy function return the y value of the point.
     */
    int getNodePy();

    /*
     * setValid function get flag and set the validNode.
     */
    void setValid(bool flag);

    /*
     * getValid function return the validNode value.
     */
    bool getValid();

    /*
     * calcNeighbors function calculate the neighbors to the current node.
     */
    void calcNeighbors();

    /*
     * getNumOfNeighbors function return numOfNeighbors value.
     */
    int getNumOfNeighbors();

    /*
     * return true if the node given is equal to the current node.
     */
    bool isEqual(Node n);

    /*
     * validateNeighbors function set the validNode value of each neighbor.
     */
    void validateNeighbors(int width, int height);

    /*
     * getNeighbor function return the i neighbor of the given node.
     */
    Node getNeighbor(int i);

    /*
     * the printing function, this function prints the point.
     */
    friend ostream &operator<<(ostream &output, const Node &N);

    /*
     * deleteNeighbors function that free the memory that was aloocated for each neighbor.
     */
    void deleteNeighbors();
};


#endif
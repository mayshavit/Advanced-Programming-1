#ifndef EX1_BFS_H
#define EX1_BFS_H


#include <queue>
#include <stack>
#include "Graph.h"

/*
 * The BFA class.
 * Runs the bfs algorithm.
 */
class BFS {
private:
    std::stack<Node> nodeStack;
    Node dsNode;
public:
    BFS();

    /*
     * The BFS constructor.
     * Gets a  node.
     */
    BFS(Node n);

    /*
     * Function that return stack of Nodes.
     */
    stack<Node> getNodeStack() const;

    /*
     * Function that returns the destination node.
     */
    Node getDsNode() const;

    /*
     * The BFS (=breadth first search) function.
     * This function gets a start Node, and end Node, and a Graph.
     * The function returns the fastest road from the start point
     * to the end point.
     */
    void breadthFirstSearch(Node startNode, Node dstNode, Graph &graph);

};


#endif

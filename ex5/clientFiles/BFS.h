#ifndef EX1_BFS_H
#define EX1_BFS_H


#include <queue>
#include <stack>
#include "Node.h"
#include "Graph.h"

/*
 * The BFA class.
 * Runs the bfs algoritem.
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
     * This function gets a start Node, an end Node, and a Graph.
     * The function returns the fastest roud from the start point
     * to the end point.
     */
    void breadthFirstSearch(Node startNode, Node dstNode, Graph &graph);

};


#endif

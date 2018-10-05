#ifndef EX1_BFS_H
#define EX1_BFS_H


#include <queue>
#include <stack>
#include "Node.h"
#include "Graph.h"

/*
 * The BFA class.
 * run the bfs algoritem.
 */
class BFS {
private:
    std::stack<Node> nodeStack;
    Node dsNode;

public:
    /*
     * the BFS constructor.
     * get node.
     */
    BFS(Node n);

    /*
     * bfs function, get node, dstination node, queue of nodes and pointer to graph.
     * it return node.
     * after calculating the shortest path between the 2 nodes.
     */
    Node bfs (Node node, Node dstN, queue<Node> nodeQueue, Graph &graph );

    /*
     * addToStack function add to the node stack the node it gets.
     */
    void addToStack(Node n);

    /*
     * printRoad function print the path that we saved in the stack.
     */
    void printRoad();
};


#endif //EX1_BFS_H

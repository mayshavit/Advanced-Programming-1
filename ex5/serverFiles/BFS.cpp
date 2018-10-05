#include <iostream>
#include <stack>
#include "BFS.h"

using namespace std;

BFS::BFS() {

}

BFS::BFS(Node n) {
    dsNode = n;
}


stack<Node> BFS::getNodeStack() const {
    return nodeStack;
}

Node BFS::getDsNode() const {
    return dsNode;
}

void BFS::breadthFirstSearch(Node startNode, Node dstNode, Graph &graph) {

    queue<Node> nodeQueue;
    stack<Node> currentNodeStack;
    Node calcNode;


    startNode.setPassed(true);
    //update the node's location in the graph
    graph.setNode(startNode);
    nodeQueue.push(startNode);

    while (!nodeQueue.empty()) {
        Node currentNode = nodeQueue.front();
        nodeQueue.pop();
        //get the updated node from the graph
        currentNode = graph.getNode(currentNode);

        //reached to dest
        if (currentNode.isEqual(dstNode)) {
            currentNodeStack.push(currentNode);
            calcNode = currentNode;
            break;
        }


        currentNode.calcNeighbors();
        graph.validateNeighbors(currentNode);
        //run on every neighbour if the current node
        for (int i = 0; i < currentNode.getNumOfNeighbors(); i++) {
            Node neighbour = currentNode.getNeighbor(i);
            if (neighbour.getValid()) {
                //if it is a valid neighbour - get the updated node from
                //the graph
                neighbour = graph.getNode(neighbour);
                if (!neighbour.getPassed()) {
                    neighbour.setPassed(true);
                    Point srcPoint(currentNode.getNodePx(), currentNode
                            .getNodePy());
                    //update the src node
                    neighbour.setSrcNode(srcPoint);
                    graph.setNode(neighbour);
                    nodeQueue.push(neighbour);
                }
            }
        }
        //frees the allocated memory
        currentNode.deleteNeighbors();
    }

    calcNode = graph.getNode(calcNode);

    //fill the stack
    while (!calcNode.getSrcNode().isEqual(startNode)) {
        Node node = calcNode.getSrcNode();
        currentNodeStack.push(node);
        calcNode = graph.getNode(node);
    }


    //fill the stack member
    int size = currentNodeStack.size();
    nodeStack.push(startNode);

    for (int i = 0; i < size; i++) {
        nodeStack.push(currentNodeStack.top());
        currentNodeStack.pop();
    }
}


#include <iostream>
#include "BFS.h"

using namespace std;

BFS::BFS(Node n) {
    dsNode = n;
}

void BFS::addToStack(Node n) {
    nodeStack.push(n);
}

void BFS::printRoad() {
    bool found = false;
    for (int i = 0; i < nodeStack.size(); i++) {
        Node node = nodeStack.top();
        if (!found) {
            cout << node << endl;
            if (nodeStack.top().isEqual(dsNode)) {
                found = true;
            }
        }
        nodeStack.pop();
    }
}

Node BFS::bfs(Node node, Node dstN, queue<Node> nodeQueue, Graph &graph) {
    int i;
    int numOfNeighbors = node.getNumOfNeighbors();

    //calc the node neighbors.
    node.calcNeighbors();
    graph.validateNeighbors(node);

    //run on every neighber.
    for (i = 0; i < numOfNeighbors; i++) {
        if (node.getNeighbor(i).getValid()) {
            if (node.getNeighbor(i).isEqual(dstN)) {
                graph.setSource(node.getNeighbor(i), node);
                addToStack(node.getNeighbor(i));
                Node n = node.getNeighbor(i);
                //delete the neighbors before return.
                node.deleteNeighbors();
                return n;
            } else if (!(graph.getSource(node.getNeighbor(i)).getPassed())) {
                nodeQueue.push(node.getNeighbor(i));
                node.setPassed(true);
                graph.setSource(node.getNeighbor(i), node);
                addToStack(node.getNeighbor(i));
            }
        }
    }
    //delete the neighbors before return.
    node.deleteNeighbors();
    nodeQueue.pop();
    Node returnNode = bfs(nodeQueue.front(), dstN, nodeQueue, graph);
    if (graph.getSource(returnNode).getValid()) {
        addToStack(graph.getSource(returnNode));
        return graph.getSource(returnNode);
    } else {
        return returnNode;
    }

}

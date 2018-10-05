#include <iostream>
#include "Point.h"
#include "Node.h"
#include "Graph.h"
#include "Grid.h"
#include "BFS.h"

using namespace std;

/**
 * The main function.
 * Responsible for running the program.
 */
int main() {
    string s;
    //getting input from the user
    cin >> s;
    if (s.length() < 11) {
        cout << "Wrong parameters" << endl;
        return 0;
    }
    //parsing the input for creating the classes
    string delimiter1 = "_";
    string delimiter2 = ",";
    string token = s.substr(0, s.find(delimiter1));
    int sizeX = atoi(token.c_str());
    s.erase(0, token.length() + 1);
    token = s.substr(0, s.find(delimiter2));
    int sizeY = atoi(token.c_str());
    s.erase(0, token.length() + 1);
    //creating the grid
    Grid grid(sizeX, sizeY);
    Graph *graph = &grid;
    queue<Node> nodeQueue;

    token = s.substr(0, s.find(delimiter1));
    sizeX = atoi(token.c_str());
    s.erase(0, token.length() + 1);
    token = s.substr(0, s.find(delimiter2));
    sizeY = atoi(token.c_str());
    s.erase(0, token.length() + 1);
    //creating the start and destination point
    Point p(sizeX, sizeY);
    Node node(p);
    Point outP(-1, -1);
    Node outN(outP);
    outN.setValid(false);

    node.setValid(true);
    node.setPassed(true);
    outN.setPassed(true);
    graph->setSource(node, outN);
    graph->getSource(node).setPassed(true);
    token = s.substr(0, s.find(delimiter1));
    sizeX = atoi(token.c_str());
    s.erase(0, token.length() + 1);
    sizeY = atoi(s.c_str());
    Point dstP(sizeX, sizeY);
    Node dstN(dstP);
    dstN.setValid(true);

    nodeQueue.push(node);
    BFS bfs(dstN);
    //run the bfs algorithm
    Node returnNode = bfs.bfs(node, dstN, nodeQueue, *graph);
    if (graph->getSource(returnNode).getValid()) {
        bfs.addToStack(graph->getSource(returnNode));
    }
    //printing the road by the bfs
    bfs.printRoad();
    return 0;
}

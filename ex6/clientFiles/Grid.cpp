#include "Grid.h"


Grid::Grid() {

}

Grid::~Grid() {

}

Grid::Grid(int width, int height) {
    sizeX = width;
    sizeY = height;

    vector<vector<Node >> matrix(sizeX, vector<Node>(sizeY));
    grid = matrix;

    //set the grid
    for (int i = 0; i < sizeX; ++i) {
        for (int j = 0; j < sizeY; ++j) {
            grid[i][j].setPassed(false);
            grid[i][j] = Node(Point(i, j));
        }
    }
}

void Grid::setSource(Node node, Node sourceNode) {
    grid[node.getNodePx()][node.getNodePy()] = sourceNode;
}

Node Grid::getNode(Node node) {
    return grid[node.getNodePx()][node.getNodePy()];
}

void Grid::validateNeighbors(Node node) {
    node.validateNeighbors(sizeX, sizeY);
}

void Grid::setNode(Node node) {
    grid[node.getNodePx()][node.getNodePy()] = node;
}

void Grid::resetGraph() {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            grid[i][j].setPassed(false);
            grid[i][j] = Node(Point(i, j));
        }
    }
}

int Grid::getWidth() {
    return sizeX;
}

int Grid::getHeight() {
    return sizeY;
}


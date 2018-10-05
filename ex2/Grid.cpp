//
// Created by eliyagvili on 23/11/16.
//

#include "Grid.h"

Grid::Grid() {

}

Grid::Grid(int width, int height) {
    sizeX = width;
    sizeY = height;
}

void Grid::setSource(Node node, Node sourceNode) {
    grid[node.getNodePx()][node.getNodePy()] = sourceNode;
}

Node Grid::getSource(Node node) {
    return grid[node.getNodePx()][node.getNodePy()];
}

void Grid::validateNeighbors(Node node) {
    node.validateNeighbors(sizeX, sizeY);
}


int Grid::getWidth() {
    return sizeX;
}

int Grid::getHeight() {
    return sizeY;
}

bool Grid::isEqual(Grid g) {
    return ((sizeX == g.getWidth()) && (sizeY == getHeight()));
}


#include "Grid.h"

Grid::Grid()
{

}

Grid::Grid(int width, int height)
{
    sizeX = width;
    sizeY = height;
}

void Grid::setSource(Node node , Node sourceNode)
{
    grid[node.getNodePx()][node.getNodePy()] = sourceNode;
}

Node Grid::getSource(Node node)
{
    return grid[node.getNodePx()][node.getNodePy()];
}

void Grid::validateNeighbors(Node node)
{
    node.validateNeighbors(sizeX , sizeY);
}
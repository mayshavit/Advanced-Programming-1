#include <stdio.h>
#include "DFSTree.h"

DFSTree::DFSTree(int givenSize, int givenValue) {
    value = givenValue;
    visited = false;
    left = right = NULL;
    if (givenSize > 0) {
        givenSize -= 1;
        givenValue += 1;
        left = new DFSTree(givenSize, givenValue);
        right = new DFSTree(givenSize,givenValue);
    }
}

DFSTree::DFSTree() {
    left = right = NULL;
}

DFSTree::~DFSTree(){
    delete left;
    delete right;
}


void DFSTree::dfs(DFSTree *tree) {

    DFSTree *currentTree = tree->getLeft();
    if ((tree->getLeft() != NULL) && (!currentTree->isVisited())) {
        dfs(currentTree);
    }

    currentTree = tree->getRight();
    if ((tree->getRight() != NULL) && (!currentTree->isVisited())) {
        dfs(currentTree);
    }
}

DFSTree *DFSTree::getLeft() const {
    return left;
}

DFSTree *DFSTree::getRight() const {
    return right;
}

int DFSTree::getValue() const {
    return value;
}

bool DFSTree::isVisited() const {
    return visited;
}
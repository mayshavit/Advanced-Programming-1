
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "DFSTree.h"

using namespace std;
/********************************************************************
 * The main function of the progaram.
 * This program gets a size parameter, builds a binary complete tree,
 * and travels on its branches in a DFS way.
 ********************************************************************/
int main(int argc, char* argv[]) {
    //If we got parameters.
    if (argc==2){
        double size = atoi(argv[1]);
        int height = (int)(log(size)/log(2));
        //Building a new complete tree.
        DFSTree* tree = new DFSTree(height,0);
        //Travels on the tree in a DFS way.
        tree->dfs(tree);
        delete tree;
        //if we got no parameters
    } else{
        cout<<"Wrong parameters"<<endl;
    }
    return 0;
}


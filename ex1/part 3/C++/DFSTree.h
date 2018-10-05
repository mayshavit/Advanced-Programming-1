#ifndef DFS_RETREE_H
#define DFS_RETREE_H

/********************************************************************
 * The DFSTree class.
 * This class builds a complete tree (all leaves in the last level of
 * the tree). Every value of a leave - represents the level of the
 * leaf in the tree.
 * Then, the dfs function travels on the tree.
 ********************************************************************/
class DFSTree {
private:
    DFSTree *left;
    DFSTree *right;
    int value;
    bool visited;
public:
    /***********************************************************
     * The constructor function - this function gets a size and
     * a value, and builds a complete tree by the given size.
     **********************************************************/

    DFSTree(int givenSize, int givenValue);
    /**********************************************************
     * The construcor function - initialize the left-tree and
     * the right-tree.
     *********************************************************/
    DFSTree();

    /**********************************************************
     * The destructor function - frees the memory that was
     * used during the program.
     *********************************************************/
    ~DFSTree();

    /**********************************************************
     * The dfs function.
     * This function gets a tree, and travels on it in a dfs
     * way - first to the most down-left leaf, until the most
     * down-right leaf.
     *********************************************************/
    void dfs(DFSTree *tree);

    /**********************************************************
     * The getLeft function.
     * This function returns the left tree of the tree.
     *********************************************************/
    DFSTree *getLeft() const;

    /**********************************************************
     * The getRight function.
     * This function returns the right tree of the tree.
     *********************************************************/
    DFSTree *getRight() const;

    /**********************************************************
     * The getValue function.
     * This function returns the value of the tree.
     **********************************************************/
    int getValue() const;

    /**
     * The isVisited function.
     * This function checks if the node was visited.
     */
    bool isVisited() const;
};

#endif

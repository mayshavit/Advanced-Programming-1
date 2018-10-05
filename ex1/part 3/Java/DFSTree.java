/**
 * The DFS class.
 * This class builds a complete tree (all leaves in he last level of the tree).
 * Every value of a leave - represents the level of the leave in the tree.
 * Then, the dfs function travels on the tree.
 * @author Eliya & May.
 *
 */
public class DFSTree {
	//members
	private DFSTree leftTree;
	private DFSTree rightTree;
	private int value;
	private boolean visited;
	
	/**
	 * The constructor function - this function gets a size and a value, and
	 * builds a complete tree by the given size.
	 * @param givenSize - indicates the size of the tree.
	 * @param givenValue - the given value to the leave.
	 */
	public DFSTree(int givenSize, Integer givenValue) {
		this.value = givenValue;
		this.visited = false;
		this.leftTree = null;
		this.rightTree = null;
		if (givenSize > 0) {
			givenSize -= 1;
			givenValue += 1;
			this.leftTree = new DFSTree(givenSize, givenValue);
			this.rightTree = new DFSTree(givenSize, givenValue);
		}
	}
	
	/**
	 * The constructor function - initialize the left-tree and the right tree.
	 */
	public DFSTree (){
		this.leftTree = null;
		this.rightTree = null;
	}
	
	/**
	 * The dfs function.
	 * This function gets a tree, and travels on it in a dfs way - first to
	 * the most down-left tree leaf, until the most down-right leaf.
	 * @param tree - the tree we travels on.
	 */
	public void dfs(DFSTree tree) {
		DFSTree currentTree = tree.getLeftTree();
		if ((currentTree != null) && (!currentTree.isVisited())) {
			dfs(currentTree);
		}
		currentTree = tree.getRightTree();
		if ((currentTree != null) && (!currentTree.isVisited())) {
			dfs(currentTree);
		}
	}
	
	/**
	 * The getLeftTree function.
	 * This function returns the left tree of the tree.
	 * @return - The left tree of the tree.
	 */
	public DFSTree getLeftTree() {
		return this.leftTree;
	}
	
	/**
	 * The getRightTree function.
	 * This function returns the right tree of the tree.
	 * @return - The right tree of the tree.
	 */
	public DFSTree getRightTree() {
		return this.rightTree;
	}

	/**
	 * The getValue function.
	 * This function returns the value of the tree.
	 * @return
	 */
	public int getValue() {
		return this.value;
	}
	
	/**
	 * The isVisited function.
	 * This function checks if the node was visited.
	 * @return
	 */
	public boolean isVisited() {
		return this.visited;
	}

}

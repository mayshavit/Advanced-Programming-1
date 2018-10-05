
public class Main {
	/**
	 * The main function of the program.
	 * This program gets a size parameter, builds a binary complete tree,
	 * and travels on its branches in a DFS way.
	 * @param args - gets the size of the tree.
	 */
	public static void main(String[] args) {
		//If we got parameters
		if (args.length == 1) {
			double size = Double.parseDouble(args[0]);
			int height = (int) (Math.log(size) / Math.log(2));
			//Building a new complete tree.
			DFSTree tree = new DFSTree(height, 0);
			//Travels on the tree in a DFS tree.
			tree.dfs(tree);
			//if we got no parameters
		} else {
			System.out.println("Wrong parameters");
		}
	}

}

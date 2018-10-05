import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 * The Main class.
 * This class is responsible for running the program.
 * @author may
 *
 */
public class GUI extends Application {

	// members
	public static BufferedReader in;
	public static MainController mainController;
	

	public void setObstacles(MainController mc) {
		int x, y;

		try {
			int num = Integer.parseInt(in.readLine());
			mc.obstacles = new ArrayList<Point>();
			for (int i = 0; i < num; i++) {
				x = Integer.parseInt(in.readLine());
				y = Integer.parseInt(in.readLine());
				mc.obstacles.add(new Point(x, y));
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	/**
	 * The start function.
	 * This function builds the GUI.
	 * @param primaryStage - for GUI.
	 */
	public void start(Stage primaryStage) throws IOException {
		
		int width = Integer.parseInt(in.readLine());
		int height = Integer.parseInt(in.readLine());
		

		//update the main-controller parameters
		mainController.gridHeight = height;
		mainController.gridWidth = width;
		mainController.setRectangleSize(width, height);
		setObstacles(mainController);
		

		//create the grid
		Parent root = FXMLLoader.load(getClass().getResource("main.fxml"));
		primaryStage.setTitle("Taxi Center");		

		Scene scene = new Scene(root, 1250, 750);
		scene.getStylesheets().add(getClass()
				.getResource("main.css").toExternalForm());
		

		primaryStage.setScene(scene);
		primaryStage.show();
	}

	/**
	 * The main function.
	 * This function runs the program.
	 * @param args - the port number and the local host number.
	 */
	public static void main(String[] args) {
		int portNum = -1;
		String localHost = "";
		mainController = new MainController();
		if (args.length == 2) {
			portNum = Integer.parseInt(args[1]);
			
		} else {
			System.exit(0);
		}
		try {
			localHost = args[0];
			Socket socket = new Socket(localHost, portNum);
			PrintWriter out = new PrintWriter(
					      socket.getOutputStream(), true);
			//update the members
			in = new BufferedReader
					(new InputStreamReader
						(socket.getInputStream()));
			mainController.portNum = portNum;
			mainController.localHost = localHost;
			mainController.in=in;
			mainController.out=out;
			mainController.socket=socket;
			launch(args);
		} catch (Exception e) {
			
		}
	}
}

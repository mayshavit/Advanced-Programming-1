import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;
import javafx.fxml.FXML;
import javafx.geometry.Insets;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.paint.ImagePattern;
import javafx.scene.shape.Rectangle;

/**
 * The MainController class. This class builds the GUI - the grid, the text
 * fields and the labels, and runs the program according to the events on the
 * screen.
 * 
 * @author may
 *
 */
public class MainController {

	// members
	public static int gridWidth;
	public static int gridHeight;
	public static ArrayList<Point> obstacles;
	public static int counter;
	public static BufferedReader in;
	public static PrintWriter out;
	public static Socket socket;
	public static int portNum;
	public static String localHost;
	private static int rectangleSize;
	public int numOfDrivers;
	private boolean shouldReciveDrivres;
	private boolean startReceive;
	private int expectedSize;
	private ArrayList<Driver> drivers;

	// FXML members
	@FXML
	GridPane gridPane;

	@FXML
	Rectangle rect, obstacle;

	@FXML
	TextField txtFlow, txtDriver;

	@FXML
	Label timeLable, errorLable;

	@FXML
	/**
	 * The initialize function. This function builds the grid, and updates
	 * the members.
	 */
	void initialize() {

		counter = 0;
		shouldReciveDrivres = false;
		startReceive = false;
		gridPane.setPadding(new Insets(20, 5, 20, 5));
		for (int i = 0; i < gridWidth; i++) {
			for (int j = 0; j < gridHeight; j++) {
				setRectangleOnGridPane(
					Color.DARKGRAY, null, j, i);
			}
		}

		for (int i = 0; i < obstacles.size(); i++) {
			setRectangleOnGridPane(Color.ALICEBLUE, null,
				gridHeight - 1 - obstacles.get(i).y, 
						obstacles.get(i).x);
		}

		timeLable.setText(String.valueOf(counter));
		drivers = new ArrayList<Driver>();
	}

	@FXML
	/**
	 * The handleEnter function. This function changes the grid according
	 * to the input the user had been given.
	 * 
	 * @param event
	 *            - to get the input.
	 */
	public void handleEnter(KeyEvent event) {
		errorLable.setText("");

		if (event.getCode() == KeyCode.ENTER) {
			String data = txtFlow.getText();
			txtFlow.clear();

			// send the data to the server
			out.println(data);
			// check if the text is correct
			boolean isCorrect = handleError();

			// if it is correct and the program should receive
			// a number of drivers
			if (shouldReciveDrivres) {
				if (isCorrect) {
					numOfDrivers = Integer.parseInt(data);
					expectedSize = numOfDrivers;
					shouldReciveDrivres = false;
					// so we receive the drivers
					startReceive = true;
					return;
				}
			}

			// check the unique numbers
			if ((isCorrect) && (data.length() == 1)) {
				int taskNumber = Integer.parseInt(data);
				switch (taskNumber) {
				case 1:
					shouldReciveDrivres = true;
					break;
				case 9:
					updateLocation();
					break;
				case 7:
					try {
						socket.close();
						System.exit(1);
					} catch (IOException e) {
						e.printStackTrace();
					}
					break;
				default:
					break;
				}
			}
		}
	}

	@FXML
	/**
	 * The handleError function. This function gets a string from the
	 * server, if the string is "-1", then the input was wrong, 
	 * therefore - the error label will display "-1".
	 * 
	 * @return boolean, true if the input was correct, flase if the 
	 * input was wrong.
	 */
	public boolean handleError() {
		String data = null;

		try {
			data = in.readLine();
		} catch (IOException e) {
			e.printStackTrace();
		}

		// wrong input
		if (data.equals("-1")) {
			errorLable.setText("-1");
			return false;
		}
		return true;
	}

	@FXML
	/**
	 * The reciveDrivers function. This function opens a c++ program
	 * for each client/ driver, and adds if to the drivers list by 
	 * calling the "addDrivers" function.
	 * 
	 * @param event
	 *            - to send the server the information about 
	 * 		each driver.
	 */
	public void reciveDrivers(KeyEvent event) {

		String[] params = new String[4];
		params[0] = "./client.out";
		params[1] = localHost;
		params[3] = txtDriver.getText();

		// if we should get drivers
		if (startReceive) {
			if (event.getCode() == KeyCode.ENTER) {
				params[2] = String.valueOf(portNum);
				txtDriver.clear();
				// open a c++ program for the client
				try {
					Runtime.getRuntime().exec(params);
				} catch (IOException e) {
					e.printStackTrace();
				}
				numOfDrivers--;
				// a program was opened for each driver
				if (numOfDrivers == 0) {
					startReceive = false;
					// add the drivers to the drivers list
					addDrives();
				}
			}
		}
	}

	@FXML
	/**
	 * The update location function. This function is called when the
	 * user had entered "9", it gets the new location from the server
	 * and update the grid according to the given information.
	 */
	public void updateLocation() {
		String strX, strY, id;
		int drivePlace;

		// increase the time of the program.
		counter++;
		timeLable.setText(String.valueOf(counter));

		for (int i = 0; i < drivers.size(); i++) {
			try {
				id = in.readLine();
				strX = in.readLine();
				strY = in.readLine();

				int x = Integer.parseInt(strX);
				int y = Integer.parseInt(strY);

				// get the relevant driver.
				drivePlace = findDriverByID(
						Integer.parseInt(id));
				Driver driver = drivers.get(drivePlace);

				setRectangleOnGridPane(Color.DARKGRAY, null,
					gridHeight - 1 - driver.location.y, 
					driver.location.x);

				setRectangleOnGridPane(null,
					      new ImagePattern(driver.image),
						      gridHeight - 1 - y, x);

				// update the new location of the driver
				drivers.get(drivePlace).location.x = x;
				drivers.get(drivePlace).location.y = y;
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	/**
	 * The getPictureForCab function. This function get a string,
	 * and returns the relevant picture.
	 * 
	 * @param string
	 *            - to get the correct picture.
	 * @return Image - the relevant picture for the cab.
	 */
	Image getPictureForCab(String string) {
		Image image;

		switch (string) {
		case "0":
			image = new Image("/RED.jpg");
			break;
		case "1":
			image = new Image("/BLUE.jpg");
			break;
		case "2":
			image = new Image("/GREEN.jpg");
			break;
		case "3":
			image = new Image("/PINK.jpg");
			break;
		case "4":
			image = new Image("/WHITE.jpg");
			break;
		default:
			image = null;
			break;
		}
		return image;
	}

	/**
	 * The addDrivers function. This function add the drivers to the
	 * drivers list, according to the information it gets from
	 * the server.
	 */
	void addDrives() {
		String x, y, id, cabColor;
		for (int i = 0; i < expectedSize; i++) {
			try {
				id = in.readLine();
				x = in.readLine();
				y = in.readLine();
				cabColor = in.readLine();

				Image image = getPictureForCab(cabColor);

				Point point = new Point(
						Integer.parseInt(x), 
							Integer.parseInt(y));
				Driver driver = new Driver(
							Integer.parseInt(id),
								image, point);
				drivers.add(driver);

				setRectangleOnGridPane(null, 
						new ImagePattern(image),
						gridHeight - 1 - 
							Integer.parseInt(y),
							Integer.parseInt(x));
			} catch (Exception e) {
			}
		}
	}

	int findDriverByID(int givenID) {
		int place = -1;
		for (int i = 0; i < drivers.size(); i++) {
			if (drivers.get(i).id == givenID) {
				place = i;

			}
		}
		return place;
	}

	/**
	 * The setRectangleSize function. This function sets the rectangleSize
	 * member by the minimum between the height and the width of the grid.
	 * 
	 * @param width
	 *            - the width of the grid.
	 * @param height
	 *            - the height of the grid.
	 */
	void setRectangleSize(int width, int height) {
		rectangleSize = Math.min(checkByHeight(height), 
							checkByWidth(width));
	}

	/**
	 * The checkByHeight function. This function returns the relevant size
	 * according to the height of the grid.
	 * 
	 * @param height
	 *            - the height of the grid.
	 * @return int - the relevant size.
	 */
	int checkByHeight(int height) {
		if (height < 11) {
			return 60;
		} else if (height < 28) {
			return 20;
		} else if (height < 49) {
			return 10;
		} else {
			return 4;
		}
	}

	/**
	 * The checkByHeight function. This function returns the relevant size
	 * according to the width of the grid.
	 * 
	 * @param width
	 *            - the width of the grid.
	 * @return int - the relevant size.
	 */
	int checkByWidth(int width) {
		if (width < 21) {
			return 60;
		} else if (width < 53) {
			return 20;
		} else if (width < 93) {
			return 10;
		} else {
			return 4;
		}
	}

	/**
	 * The setRectangleOnGridPane function. This function sets a new
	 * rectangle on the grid according to the given parameters.
	 * 
	 * @param color
	 *            - for the rectangle fill (null if the fill is an image).
	 * @param image
	 *            - for the rectangle fill (null if the fill is a color.
	 * @param rowIndex
	 *            - to set the row index.
	 * @param columnIndex
	 *            - to set the column index.
	 */
	void setRectangleOnGridPane(Color color, ImagePattern image, 
					int rowIndex, int columnIndex) {
		rect = new Rectangle(rectangleSize, rectangleSize);

		if (color != null) {
			rect.setFill(color);
		} else if (image != null) {
			rect.setFill(image);
		}

		rect.setStroke(Color.DARKCYAN);
		gridPane.setRowIndex(rect, rowIndex);
		gridPane.setColumnIndex(rect, columnIndex);
		gridPane.getChildren().add(rect);
	}
}

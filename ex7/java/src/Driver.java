import javafx.scene.image.Image;

/**
 * The Driver class. This class represents a client - driver. Each driver has
 * an id number, a location (point), and an image that represents the cab.
 * 
 * @author may
 *
 */
public class Driver {

	// members
	public int id;
	public Image image;
	public Point location;

	// constructor
	public Driver(int givenID, Image givenImage, Point givenLocation) {
		id = givenID;
		image = givenImage;
		location = givenLocation;
	}

}

We've chose to do the original excersize - the 10% with the client and server communication.
We've also chose to do the bonus - dynamic grid.

The program flow:
(After compilation of the 2 programs - java and cpp.)

**********************************************************************************************
NOTE: The program run line by line, means you need to press the enter button after every line.
NOTE: By instructor permission, the program flow that is described below is correct.
**********************************************************************************************

1. Open a terminal for the server.
2. Run the command: "./server.out <port_number>".
3. Insert the details of the grid - the height and width of the grid, the number of obstacels
   and the obstacles.
   NOTE: If there is any mistake in the input at that stage - the program will print "-1" in
         the server terminal (like previos excercises), because there was no instruction
         about it.
4. Open another terminal for the GUI.
5. Run the command: "java -jar gui.jar <local_host> <port_number>".
6. A GUI will Open.
7. About the GUI:
	a. The GUI is constracted by 4 boxes, and the grid.
	b. About the grid:
		- The natural color of each square is gray.
		- The obstacels are colored in white.
		- The dimentions of the grid are from (0,0) (the left - buttom corner) to
		  (height-1, height-1) (the upper - right corner).
		  For example: if the input was "6 6" for the grid, the dimentions will be
			       from (0,0) to (5,5).
	c. About the 4 boxes:
	   __________________________________________________________
	  |__flow__box__|__drivers_box__|___time_box___|__error_box__|

		- The left box is intended for the program flow - the trips and cabs, "9"
		  "7" and "1" for drivers and right after the number of drivers.
		- The box after is intended for the drivers flow - details of every driver.
		- The purpel box is intended for the time program - changes every time the
		  user pressed "9".
		- The right box is intended for errors - it will display "-1" every time the
		  input was wrong.
8. Insert the program flow in the left box (press "enter" after every input insert).
9. When you press "1" (and then "enter") in the left box, insert also the number of drivers
   and then "enter", then go to the box that is right from it, and insert the drivers details.
   The cabs will appear on the grid after the last driver was inserted.
10. Go back to the left box, and insert the program flow.
11. Every time the "9" button will be pressed, the time of the program will advance by one,
    the time box will display it, and the cabs will move.
12. When the "7" button will be pressed, the server (and its clients) will be closed, and so
    the GUI program.

Example:
$ ./server.out 40000
6 6 
1
1,1
$ java -jar gui.jar 127.0.0.1 40000
  through the gui text field (the left box):
3 enter
0,1,H,R enter
2 enter
0,0,0,2,2,1,20,1 enter
1 enter
1 enter
  through the drivers text field:
0,30,M,1,0                         // a red cab will appear in (0,0)
  through the gui text field (the left box):
9 enter
9 enter                            // the cab will move
.
.
.
9 enter
7 enter                            // all programs will be closed - the GUI, the server and the drivers (the clients).

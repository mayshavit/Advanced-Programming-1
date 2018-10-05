a.out: main.o BFS.o Node.o Point.o Grid.o Graph.o
	g++ main.o BFS.o Node.o Point.o Grid.o Graph.o
Node.o: Node.cpp Node.h
	g++ -c -std=c++0x Node.cpp
BFS.o: BFS.cpp BFS.h
	g++ -c -std=c++0x BFS.cpp
Point.o: Point.cpp Point.h
	g++ -c -std=c++0x Point.cpp
Grid.o: Grid.cpp Grid.h
	g++ -c -std=c++0x Grid.cpp
Graph.o: Graph.cpp Graph.h
	g++ -c -std=c++0x Graph.cpp
main.o: main.cpp Node.h Point.h Graph.h Grid.h BFS.h
	g++ -c -std=c++0x main.cpp
clean:
	rm *.o 	

a.out: main.o DFSTree.o
	g++ main.o DFSTree.o

DFSTree.o: DFSTree.cpp DFSTree.h
	g++ -Wall -c DFSTree.cpp

main.o: main.cpp
	g++ -Wall -c main.cpp

clean:
	\r *.o *~ a.out

tar:
	tar cfv a.out.tar main.cpp DFSTree.cpp DFSTree.h

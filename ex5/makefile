all:

	g++ *clientFiles/*.cpp *clientFiles/*.h *clientFiles/sockets/*.cpp *clientFiles/sockets/*.h -lm -ansi -lboost_serialization -o client.out -std=c++0x -pthread

	g++ *serverFiles/*.cpp *serverFiles/*.h *serverFiles/sockets/*.cpp *serverFiles/sockets/*.h -lm -ansi -lboost_serialization -o server.out -std=c++0x -pthread

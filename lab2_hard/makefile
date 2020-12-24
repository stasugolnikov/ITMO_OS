CC=g++
FLAGS=-w -o
STAND=--std=c++17

client: client.cpp
	$(CC) $(STAND) client.cpp wrappers.cpp $(FLAGS) client


server: server.cpp
	$(CC) $(STAND) server.cpp wrappers.cpp $(FLAGS) server


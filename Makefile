CC=g++
CPPFLAGS=-W -Wall -g
LFlag=-lncurses

all:pushbox

pushbox:map.o game.o main.o
	$(CC) -o pushbox map.o game.o main.o $(LFlag)

map.o: map.cpp map.h 
	$(CC) -c -o map.o map.cpp $(LFlag)

game.o : game.cpp game.h map.h
	$(CC) -c -o game.o game.cpp $(LFlag)

main.o:main.cpp
	$(CC) -c -o main.o main.cpp $(LFlag)

clean:
	rm -rf *.o

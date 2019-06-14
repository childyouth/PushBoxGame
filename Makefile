CC=g++
CPPFLAGS=-W -Wall -g
LFlag=-lncurses

all:pushbox

pushbox:gameobject.o map.o game.o main.o
	$(CC) -o pushbox gameobject.o map.o game.o main.o $(LFlag)

gameobject.o: gameobject.cpp gameobject.h
	$(CC) -c -o gameobject.o gameobject.cpp $(LFlag)

map.o: map.cpp map.h 
	$(CC) -c -o map.o map.cpp $(LFlag)

game.o : game.cpp game.h map.h
	$(CC) -c -o game.o game.cpp $(LFlag)

main.o:main.cpp
	$(CC) -c -o main.o main.cpp $(LFlag)

clean:
	rm -rf *.o

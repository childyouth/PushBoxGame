CC=g++
CPPFLAGS=-W -Wall
LFlag=-lncurses

all:pushbox

pushbox:map.o main.o
	$(CC) -o pushbox map.o main.o $(LFlag)

map.o: map.cpp map.h 
	$(CC) -c -o map.o map.cpp $(LFlag)

main.o:main.cpp
	$(CC) -c -o main.o main.cpp $(LFlag)

clean:
	rm -rf *.o

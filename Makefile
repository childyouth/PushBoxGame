CC=g++
CFlag=-W -Wall
LFlag=-lncurses

all:main

pushbox:map.o main.o
	$(CC) $(CFlag) -o pushbox map.o main.o 

map.o:map.cpp
	$(CC) $(CFlag) -c -o map.o map.cpp

main.o:main.cpp
	$(CC) $(CFlag) -c -o main.o main.cpp $(LFlag)

clean:
	rm -rf *.o

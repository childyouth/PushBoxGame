#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <fstream>
using namespace std;
/****************
map클래스
벽 1
상자 2
목적지 3
바깥 4
****************/
class map
{
public:
	int col, row;
	int **m;
	map(int c, int r);
	void setMap(char filename[]);
	void checkMapData();
};
#endif

#ifndef MAP_H
#define MAP_H
#define MAX_LINE 30
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/****************
map클래스
벽 1
상자 2
목적지 3
바깥 4
****************/
class Point{
		friend class map;
		int col, row;
		Point(){}
		Point(int _col, int _row){col = _col; row=_row;}
	};
class map
{
public:
	int num_maps;
	int ***maps;
	Point *chracters; // 캐릭터의 위치
	Point *map_sizes; // 맵 사이즈

	map(){};
	void initMap();
	void setMap(int, int, int, string temp[MAX_LINE]);
	int** getMap(int);
	Point getChracter(int);
	Point getMapSize(int);
	int getMapNum();
	void checkMapData(int);
};
#endif

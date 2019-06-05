#ifndef MAP_H
#define MAP_H
#define MAX_LINE 30
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
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
	vector<vector<vector<int> > > maps;
	Point *chracters; // 캐릭터의 위치
	Point *map_sizes; // 맵 사이즈

	map(){};
	void initMap(); // 맵의 초기 설정, 맵 크기, 캐릭터의 위치
	void setMap(int, int, int, vector<string>); // 맵 데이터를 실질적을 저장
	vector<vector<int> > getMap(int); // 맵데이터
	Point getChracter(int); // 캐릭터 위치
	Point getMapSize(int); // 맵 사이즈
	int getMapNum(); // 맵 개수
	void checkMapData(int); // 맵 테스트
};
#endif

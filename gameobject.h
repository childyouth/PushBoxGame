#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include<iostream>
#include<vector>
#include<ncurses.h>
#include"point.h"
using namespace std;

class Character;
class Destination;
class Box;

class GameObject {
public:
	vector<Box> *boxes;	// 박스들
	vector<Destination> *destinations; // 목적지
	Character *character;

	point p; // 각 오브젝트들의 위치
	bool can_move; // 이동 가능 객체인지 아닌지
	int data; // 데이터값 벽 1, 상자 2, 목적지 3, 바깥 4
	GameObject() {}
	GameObject(int x, int y, int _data, bool _can_move = false) :p(point(x, y)), data(_data), can_move(_can_move) {}
	GameObject(point p, int _data, bool _can_move = false) :p(p), data(_data), can_move(_can_move) {}
	virtual int move(int s,int c);
	int getType(){ return data; }

	bool isComplete();

	friend ostream& operator<<(ostream& o, const GameObject &obj) {
		return o << obj.data;
	}
};
#endif

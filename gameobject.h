#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include<iostream>
#include<vector>
#include<ncurses.h>
#include"point.h"
using namespace std;
class GameObject {
public:
	static vector<vector<GameObject> > MAP;	// ���� ��
	static vector<GameObject> boxes;	// �ڽ�
	static vector<point> dest;			// �ڽ��� ������
	// static vector<point> dest;		
	point p;
	bool can_move;
	int data;
	GameObject() {}
	GameObject(int x, int y, int _data = 0, bool _can_move = false) :p(point(x, y)), data(_data), can_move(_can_move) {

	}
	GameObject(point p, int _data = 0, bool _can_move = false) :p(p), data(_data), can_move(_can_move) {

	}
	int move(int s,int c);
	bool is_clear();
	void setMAP(vector<vector<int> > currentMap);
	friend ostream& operator<<(ostream& o, const GameObject &obj) {
		return o << obj.data;
	}
};
#endif

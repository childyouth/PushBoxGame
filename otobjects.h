#ifndef OTOBJECTS_H
#define OTOOBJECTS_H

#include "gameobject.h"

class Character : GameObject{
public:
	Character(){}
	Character(point p, int _data = '@', bool _can_move = true) : GameObject(p, _data, _can_move){}
	Character(int x, int y, int _data = '@', bool _can_move = true) : GameObject(x, y, _data, _can_move){}
	int move(int s, int c);
};

class Box : GameObject{
public:
	Box(){}
	Box(point p, int _data = 2, bool _can_move = true) : GameObject(p, _data, _can_move){}
	Box(int x, int y, int _data = 2, bool _can_move = true) : GameObject(x, y, _data, _can_move){}
	int move(int s, int c);
};

class Destination : GameObject{
public:
	Destination(){}
	Destination(point p, int _data = 3, bool _can_move = false) : GameObject(p, _data, _can_move){}
	Destination(int x, int y, int _data = 3, bool _can_move = false) : GameObject(x, y, _data, _can_move){}
	int move(int s, int c);
};

#endif
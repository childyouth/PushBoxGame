#ifndef OTOBJECTS_H
#define OTOOBJECTS_H

#include "gameobject.h"

class Character : GameObject{
public:
	Character(){}
	Character(point p, int _data = '@', bool _can_move = true) : GameObject(p, _data, _can_move){}
	Character(int x, int y, int _data = '@', bool _can_move = true) : GameObject(x, y, _data, _can_move){}
	Character(const Character& g) :GameObject(g.p, g.data, g.can_move) { }
	virtual int move(int s, int c);
	virtual point getPoint(){ return p; }
};

class Box : GameObject{
	bool complete = false;
public:
	Box(){}
	Box(point p, int _data = 2, bool _can_move = true) : GameObject(p, _data, _can_move){}
	Box(int x, int y, int _data = 2, bool _can_move = true) : GameObject(x, y, _data, _can_move){}
	Box(const Box& g) :GameObject(g.p, g.data, g.can_move) { complete = g.complete; }
	bool isComplete();
	virtual int move(int s, int c);
	virtual point getPoint(){ return p; }
};

class Destination : GameObject{
public:
	Destination(){}
	Destination(point p, int _data = 3, bool _can_move = false) : GameObject(p, _data, _can_move){}
	Destination(int x, int y, int _data = 3, bool _can_move = false) : GameObject(x, y, _data, _can_move){}
	Destination(const Destination& g) :GameObject(g.p, g.data, g.can_move) { }
	virtual int move(int s, int c);
	virtual point getPoint(){ return p; }
};

#endif
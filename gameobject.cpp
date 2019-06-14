#include"gameobject.h"
int GameObject::move(int s,int c) {
	if (!can_move)
		return -1;
	int _x = 0, _y = 0;
	switch (s) {
	case 1: _x = 1; break;
	case 2: _x = -1; break;
	case 3: _y = 1; break;
	case 4: _y = -1; break;
	default: cout << "1 : x+1 / 2 : x-1 / 3 : y+1 / 4 : y-1" << endl; return -2;
	}
	int x = p.col + _x;
	int y = p.row + _y;
	for (int i = 0; i < boxes.size(); i++) {
		if (boxes[i].p.col == x && boxes[i].p.row == y) {
			if (c == 2) {
				return -1;
			}
			if (boxes[i].move(s, 2) == 0) {
				p = point(x, y);
				return 0;
			}
			return -1;
		}
	}
	if (MAP[x][y].data == 0 || MAP[x][y].data == 3) {
		p = point(x, y);
		return 0;
	}
	else if (MAP[x][y].data == 1) {
		return -1;
	}
	return 0;
}

vector<vector<GameObject> > GameObject::MAP;
vector<GameObject> GameObject::boxes;
vector<point> GameObject::dest;

bool is_clear() {
	for (int i = 0; i < GameObject::boxes.size(); i++) {
		for (int j = 0; j < GameObject::dest.size(); j++) {
			if (GameObject::dest[j].col == GameObject::boxes[i].p.col &&
				GameObject::dest[j].row == GameObject::boxes[i].p.row) {
				break;
			}
			if (j == GameObject::dest.size() - 1)
				return false;
		}
	}
	return true;
}

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

void GameObject::setMAP(vector<vector<int> > currentMap) {
	GameObject::MAP = vector<vector<GameObject> >();
	GameObject::boxes = vector<GameObject>();
	GameObject::dest = vector<point>();
	for (int i = 0; i < currentMap.size(); i++) {
		vector<GameObject> tmp = vector<GameObject>();
		for (int j = 0; j < currentMap[i].size(); j++) {
			int n = currentMap[i][j];
			if (n == 1 || n == 4)
				tmp.push_back(GameObject(i, j, n));
			else if (n == 2) {
				tmp.push_back(GameObject(i, j, 0, true));
				GameObject::boxes.push_back(GameObject(i, j, 2, true));
				n = 0;
			}
			else {
				if (n == 3)
					GameObject::dest.push_back(point(i, j));
				tmp.push_back(GameObject(i, j, n, true));
			}
		}
		GameObject::MAP.push_back(tmp);
	}
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

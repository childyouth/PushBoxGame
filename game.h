#ifndef GAME_H
#define GAME_H
#include "map.h"
#include <ncurses.h>

using namespace std;

// class character{
// public:
//     int x, y;
//     char characterShape;
//     character();
//     character(int, int, char c='0');
//     void move(int x, int y);
// };


class game{
private:
    WINDOW *win; // 게임 화면
    // character chrac; // chracter
    map maps; // 맵 데이터
    int maxLevel;
    int level = 0;

    point size, character;
    vector<vector<int>> currentMap;
public:
    game();
    game(WINDOW*&);
    void move(int x, int y);
    void newGame();
    void drawMap();
    void levelUp();
    point getCharater();
};

#endif
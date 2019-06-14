#ifndef GAME_H
#define GAME_H
#include "map.h"
#include "point.h"
#include <ncurses.h>

using namespace std;

class game{
private:
    WINDOW *win; // 게임 화면
    // character chrac; // chracter
    map maps; // 맵 데이터
    int maxLevel;
    int level = 0;
    bool gameEnd = false;
    bool stageEnd = false;

    point size, character;
    point beforeCharacter;
    vector<vector<int> > currentMap;
public:
    game(WINDOW*&);
    void newStage(int level=0);
    void drawMap(); 
    void drawCharacter();
    void drawBoxs(){} // 미구현
    void levelUp();
    point getCharater();
    
    void endStage();
    void endGame();
    bool isStageEnd();
    bool isGameEnd();

    // 테스트 기능 - 캐릭터가 움직인 자리에 0을 채워넣음
    void fillBeforeCharacter(){
        mvwprintw(win, beforeCharacter.row+2, beforeCharacter.col+3, "0");
        beforeCharacter = point(character.col, character.row);
    }
    // 테스트 기능 - 캐릭터의 좌표를 바꿈
    void move(int x, int y){
        character.setPoint(x, y);
    }
};

#endif

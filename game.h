#ifndef GAME_H
#define GAME_H
#include "map.h"
#include "otobjects.h"
#include "point.h"
#include <ncurses.h>

#define IN_WINDOW_X 3
#define IN_WINDOW_Y 4

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

    point size;
    GameObject objects;
    vector<vector<int> > currentMap;
public:
    game(WINDOW*&);
    void newStage(int level=0);
    void drawMap(); 
    void drawCharacter();
	void drawBoxs(); // 미구현
	void drawDestination(); 
    void levelUp();
    // GameObject& getCharater();
    
    void endStage();
    void endGame();
    bool isStageEnd();
    bool isGameEnd();
    int getMaxLevel();
    int getLevel();
    Character* getCharacter() { return objects.character; };
    
    void generateObjects();

    void setWindow(WINDOW *&another);
};

#endif

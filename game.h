#ifndef GAME_H
#define GAME_H
#include "map.h"
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
	GameObject character;
    vector<vector<int> > currentMap;
	vector<GameObject> last_box;
public:
    int move_cnt = 0;
	int box_move_cnt = 0;
    game(WINDOW*&);
    void newStage(int level=0);
    void drawMap(); 
    void drawCharacter();
	void drawBoxs(); 
	void drawDestination();
	void drawCompleteBox();
    void levelUp();
    GameObject& getCharater();
    
    void endStage();
    void endGame();
    bool isStageEnd();
    bool isGameEnd();
    int getMapNum();
    int getLevel();
	bool isBoxMoved();
	bool BoxOnDestination();
    
    void setWindow(WINDOW *&another);
};

#endif

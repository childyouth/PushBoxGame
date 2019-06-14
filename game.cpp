#include "game.h"

game::game(WINDOW *&win) {
    this->win = win; // 윈도우 설정
    maps.initMap(); // 맵 세팅
    maxLevel = maps.getMapNum();
}

void game::newStage(int level){
    // 데이터 셋
    if (level >= maxLevel) {
        char msg[] = "마지막 레벨입니다.";
        mvwprintw(win, IN_WINDOW_Y, IN_WINDOW_X, msg);
        gameEnd = true;
        return;
    }
    this->level = level;
    stageEnd = false;
    size = maps.getMapSize(level);
    character = maps.getChracter(level);
    beforeCharacter = maps.getChracter(level);
    currentMap = maps.getMap(level);
}

void game::drawMap(){
    // 맵상에 화면 그려줌
    // cout << "맵을 생성합니다." << endl;
    for(int row=0; row<size.row; row++){
        char ctemp[2];
        for(int col=0;col<size.col;col++){
        // cout << "row : " << size.row << " col : " << size.col << endl;
            sprintf(ctemp, "%d", currentMap[row][col]);
            mvwprintw(win, row+IN_WINDOW_Y, col+IN_WINDOW_X, ctemp);
        }
    }

    drawCharacter();
    drawBoxs();  
}
void game::drawCharacter(){
    mvwprintw(win, character.row+IN_WINDOW_Y, character.col+IN_WINDOW_X, "@");
}
void game::levelUp(){
    level++;
    this->newStage(level);
}
void game::endStage(){ stageEnd = true; }
void game::endGame(){ gameEnd = true; }
bool game::isStageEnd(){ return stageEnd; }
bool game::isGameEnd(){ return gameEnd; }
void game::setWindow(WINDOW *&another){ this->win = another; };
int game::getMapNum(){ return maps.getMapNum(); };
int game::getLevel(){ return level; };
point game::getCharater(){
    return character;
}
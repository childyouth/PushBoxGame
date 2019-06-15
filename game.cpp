#include "game.h"

game::game(WINDOW *&win) {
    this->win = win; // 윈도우 설정
    maps.initMap(); // 맵 세팅
    maxLevel = maps.getMapNum();
}

void game::newStage(int level){
    objects.reset(); // static data를 초기화함

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
    objects.character = new Character(maps.getChracter(level));
    currentMap = maps.getMap(level);
    generateObjects(); // 상자, 목적지 객체를 매핑합니다.
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

    drawBoxs();  
    drawCharacter();
}
void game::drawBoxs() {
	for (int i = 0; i < GameObject::boxes.size(); i++) {
		point a = GameObject::boxes[i]->getPoint();
        mvwprintw(win,  a.row + IN_WINDOW_Y
			, a.col + IN_WINDOW_X, "2");
	}
}
void game::drawCharacter(){
    mvwprintw(win, GameObject::character->getPoint().row+IN_WINDOW_Y, GameObject::character->getPoint().col+IN_WINDOW_X, "@");
}
void game::drawDestination(){
    for (int i = 0; i < GameObject::destinations.size(); i++) {
        point a = GameObject::boxes[i]->getPoint();
		mvwprintw(win, a.row+ IN_WINDOW_Y
			, a.col + IN_WINDOW_X, "3");
	}
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
int game::getMaxLevel(){ return maxLevel; };
int game::getLevel(){ return level; };

void game::generateObjects(){
    for(int row=0; row<size.row; row++){
        for(int col=0;col<size.col;col++){
            point position = point(row, col);
            if(currentMap[row][col] == 2) 
                GameObject::boxes.push_back(new Box(position));
            else if(currentMap[row][col] == 1) 
                GameObject::destinations.push_back(new Destination(position));
        }
    }
}
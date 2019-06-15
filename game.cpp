#include "game.h"

game::game(WINDOW *&win) {
    this->win = win; // 윈도우 설정
    maps.initMap(); // 맵 세팅
    maxLevel = maps.getMapNum();
}

void game::newStage(int level){
    // 데이터 셋
    if (level >= maxLevel) {
        char msg[] = "Last Level";
        mvwprintw(win, IN_WINDOW_Y, IN_WINDOW_X+10, msg);
        gameEnd = true;
        return;
    }
    move_cnt = 0;
    this->move_cnt = 0;
    this->level = level;
    stageEnd = false;
    size = maps.getMapSize(level);
    character = maps.getChracter(level);
    currentMap = maps.getMap(level);
	character.setMAP(currentMap);
    GameObject::complete.clear();
	last_box = GameObject::boxes;
}

void game::drawMap(){
    // 맵상에 화면 그려줌
    // cout << "맵을 생성합니다." << endl;
    for(int row=0; row<size.row; row++){
        char ctemp[2];
        for(int col=0;col<size.col;col++){
        // cout << "row : " << size.row << " col : " << size.col << endl;
            sprintf(ctemp, "%d", GameObject::MAP[row][col].data);
            mvwprintw(win, row+IN_WINDOW_Y, col+IN_WINDOW_X, ctemp);
        }
    }

    //drawBoxs();  
    //drawCharacter();
}
void game::drawBoxs() {
	for (int i = 0; i < GameObject::boxes.size(); i++) {
		mvwprintw(win, GameObject::boxes[i].p.col + IN_WINDOW_Y
			, GameObject::boxes[i].p.row + IN_WINDOW_X, "2");
	}
}
void game::drawDestination() {
	for (int i = 0; i < GameObject::dest.size(); i++) {
		mvwprintw(win, GameObject::dest[i].col + IN_WINDOW_Y
			, GameObject::dest[i].row + IN_WINDOW_X, "3");
	}
}
void game::drawCompleteBox() {
	for (int i = 0; i < GameObject::complete.size(); i++) {
		mvwprintw(win, GameObject::complete[i].col + IN_WINDOW_Y
			, GameObject::complete[i].row + IN_WINDOW_X, "2");
	}
}
void game::drawCharacter(){
    mvwprintw(win, character.p.col+IN_WINDOW_Y, character.p.row+IN_WINDOW_X, "@");
}
void game::levelUp(){
    level++;
    this->newStage(level);
}
void game::endStage(){ stageEnd = true; }
void game::endGame(){ gameEnd = true; }
bool game::isStageEnd(){
	stageEnd = character.is_clear();
	return stageEnd;
}
bool game::isGameEnd(){ return gameEnd; }
GameObject& game::getCharater(){
    return character;
}
bool game::isBoxMoved() {
	for (int i = 0; i < last_box.size(); i++) {
		if (last_box[i].p.col != GameObject::boxes[i].p.col ||
			last_box[i].p.row != GameObject::boxes[i].p.row) {
			last_box = GameObject::boxes;
			box_move_cnt++;
            BoxOnDestination();
			return true;
		}
	}
	return false;
}
bool game::BoxOnDestination(){
    GameObject::complete.clear();
    for (int i = 0; i < GameObject::boxes.size(); i++) {
		for (int j = 0; j < GameObject::dest.size(); j++) {
			if (GameObject::dest[j].col == GameObject::boxes[i].p.col &&
				GameObject::dest[j].row == GameObject::boxes[i].p.row) {
                GameObject::complete.push_back(last_box[i].p);
			}
		}
	}
}
void game::setWindow(WINDOW *&another){ this->win = another; };
int game::getMapNum(){ return maps.getMapNum(); };
int game::getLevel(){ return level; };

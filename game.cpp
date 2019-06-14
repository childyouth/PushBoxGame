#include "game.h"

#define WIN_SIZE_Y 18
#define WIN_SIZE_X 78

game::game() {
    win = newwin(78, 18, 1, 1); // 윈도우 설정
    maps.initMap(); // 맵 세팅
    maxLevel = maps.getMapNum();
}
game::game(WINDOW *&win) {
    this->win = win; // 윈도우 설정
    maps.initMap(); // 맵 세팅
    maxLevel = maps.getMapNum();
}
void game::move(int x, int y){
    this->character.setPoint(x, y);
}
void game::newGame(){
    // 데이터 셋
    if (level >= maxLevel) {
        cout << "최대 맵 개수" << maxLevel;
        return;
    }
    size = maps.getMapSize(level);
    character = maps.getChracter(level);
    currentMap = maps.getMap(level);
}

void game::drawMap(){
    // 맵상에 화면 그려줌
    // cout << "맵을 생성합니다." << endl;
    for(int row=0; row<size.row; row++){
        char ctemp[10];
        for(int col=0;col<size.col;col++){
        // cout << "row : " << size.row << " col : " << size.col << endl;
            sprintf(ctemp, "%d", currentMap[row][col]);
            mvwprintw(win, row+2, col+6, ctemp);
        }
    }   
}



void game::levelUp(){
    level++;
}

point game::getCharater(){
    return character;
}
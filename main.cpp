#include<ncurses.h>
#include "map.h"
#include "game.h"
#define WIN_SIZE_Y 40
#define WIN_SIZE_X 50

void init_colors();
void handle_menu_cursor(int key, int &y); // 메인 메뉴에서 커서 이동
void select_this_menu(int y); // Enter입력으로 메뉴에 따른 아이템 실행
void show_pause_screen(WINDOW *win); // P를 눌렀을 시 Pause
void gameStart(int prefix=0); // Main game loop로 들어감
void gameLoop();
void selectLevel();
void draw(WINDOW *); // gameObjects 놈들 draw

WINDOW *gamescreen, *pause, *levelSelect;
game g(gamescreen);
char temp[10];

int main(){

	initscr();

	gamescreen = newwin(WIN_SIZE_Y*0.5,WIN_SIZE_X,1,1);
	pause = newwin(6,20,WIN_SIZE_Y/3 - 6, WIN_SIZE_X/2 - 10);
	levelSelect = newwin(WIN_SIZE_Y*0.5, WIN_SIZE_X, 1, 1);
	// 게임 기본 세팅
	init_colors();
	bkgd(COLOR_PAIR(10));

	resize_term(WIN_SIZE_Y+30,WIN_SIZE_X+30);

	attron(COLOR_PAIR(1));
	border('0','0','0','0','0','0','0','0');
	attroff(COLOR_PAIR(1));

	keypad(stdscr,TRUE);
	curs_set(0);
	noecho();
	
	// 로비 띄우기
	int line = 4;
	int cursor_x=3, cursor_y=4;
	bool end = false;
	while(1){
		clear();
		char c_y = (char)cursor_y + '0';
		attron(COLOR_PAIR(2));
		mvprintw(2, cursor_x, &c_y);
		mvprintw(cursor_y, cursor_x, ">");
		attroff(COLOR_PAIR(2));
		refresh();
		
		int key = getch();
		if(key == 'q' || key == 'Q') break;
		handle_menu_cursor(key, cursor_y);
	}
	
	refresh();
	getch();
	endwin();
	return 0;
}

void init_colors(){
	start_color();
	init_pair(1, COLOR_MAGENTA, COLOR_MAGENTA); // border color
	init_pair(2, COLOR_BLACK, COLOR_WHITE); // char color
	init_pair(3, COLOR_WHITE, COLOR_BLACK); // gamescreen char color

	init_pair(9, COLOR_BLACK, COLOR_BLACK); // gaem screen color
	init_pair(10, COLOR_WHITE, COLOR_WHITE); // background color
	init_pair(11, COLOR_RED, COLOR_RED); // pause background color

	init_pair(15, COLOR_GREEN, COLOR_BLACK); // box color
	init_pair(16, COLOR_CYAN, COLOR_BLACK); // complete box color
	init_pair(17, COLOR_RED, COLOR_BLACK); // character color
	init_pair(18, COLOR_BLUE, COLOR_BLACK); // destination color

	init_pair(20, COLOR_BLACK, COLOR_BLACK); // string color
	init_pair(21, COLOR_BLUE, COLOR_RED); // pause string color
}
void handle_menu_cursor(int key, int &y){
	int max = 6, min = 4;
	switch(key){
		case KEY_UP:
			if(y>min)y--;
			break;
		case KEY_DOWN:
			if(y<max)y++;
			break;
		case 'p':
			show_pause_screen(stdscr);
			break;
		case 10:
			select_this_menu(y);
			break;
	}	
}
void show_pause_screen(WINDOW *win){
	wbkgd(pause,COLOR_PAIR(11));
	wattron(pause,COLOR_PAIR(21));
	mvwprintw(pause,1,1,"  Press Any KEY To\n      CONTINUE");
	wattroff(pause,COLOR_PAIR(21));
	wattron(pause,COLOR_PAIR(1));
	wborder(pause,'0','0','0','0','0','0','0','0');
	wattroff(pause,COLOR_PAIR(1));
	wrefresh(pause);
	getch();
	wclear(pause);
	wrefresh(pause);
	wbkgd(pause,COLOR_PAIR(9));
	touchwin(win);
}
// 번호에 맞는 옵션을 실행하도록 만들세용
void select_this_menu(int y){
	if(y == 4){
		gameStart();
	}
	if(y == 5){
		selectLevel();
	}
}
void gameStart(int prefix){
	g.setWindow(gamescreen);
		
	while(!g.isGameEnd()){
		if(prefix==0) g.newStage();
		prefix = 1;
		// 게임 기본 세팅, 윈도우 생성, 맵 그리기
		wbkgd(gamescreen,COLOR_PAIR(9));
		wattron(gamescreen,COLOR_PAIR(1));
		wborder(gamescreen,'0','0','0','0','0','0','0','0');
		wattroff(gamescreen,COLOR_PAIR(1));
		
		wattron(gamescreen, COLOR_PAIR(3));
		sprintf(temp, "%d", g.getLevel()); // int -> string
		mvwprintw(gamescreen, 1, 3, "Hurry UP! ");
		mvwprintw(gamescreen, 2, 3, "Level : ");
		mvwprintw(gamescreen, 2, 11, temp);
		wattroff(gamescreen, COLOR_PAIR(3));

		draw(gamescreen);
		
		wrefresh(gamescreen);
		
		// 메인 게임 루프실행
		gameLoop();
	}
}
void gameLoop(){
	point character = g.getCharater();
	int c_x = character.col, c_y = character.row;
	while(!g.isStageEnd()){
		int key = getch();

		switch(key){
			case KEY_LEFT:
				g.move(--c_x, c_y);break;
			case KEY_RIGHT:
				g.move(++c_x, c_y);break;
			case KEY_UP:
				g.move(c_x, --c_y);break;
			case KEY_DOWN:
				g.move(c_x, ++c_y);break;
			case 'p':
				show_pause_screen(gamescreen);break;
		}
		draw(gamescreen);
		wattron(gamescreen, COLOR_PAIR(3));
		g.fillBeforeCharacter();
		wattroff(gamescreen, COLOR_PAIR(3));

		wrefresh(gamescreen);
	}
}
void selectLevel(){
	int key, level=0, maxLevel = g.getMapNum();

	g.setWindow(levelSelect);
	wbkgd(levelSelect,COLOR_PAIR(9));
	do{
		g.newStage(level);
		wattron(levelSelect,COLOR_PAIR(1));
		wborder(levelSelect,'0','0','0','0','0','0','0','0');
		wattroff(levelSelect,COLOR_PAIR(1));

		wattron(levelSelect, COLOR_PAIR(3));
		sprintf(temp, "%d", level); // int -> string
		mvwprintw(levelSelect, 1, 3, "Current Level : ");
		mvwprintw(levelSelect, 1, 20, temp);
		wattroff(levelSelect, COLOR_PAIR(3));
		
		draw(levelSelect);
		wrefresh(levelSelect);
		
		key = getch();
		wclear(levelSelect);
		if(key == KEY_LEFT || key == KEY_DOWN){
			if(level>0) level--;
			else mvwprintw(levelSelect, 2, 3, "This level is Min Level");
		}
		else if(key == KEY_RIGHT || key == KEY_UP){
			if(level<maxLevel-1) level++;
			else mvwprintw(levelSelect, 2, 3, "T his level is Max Level");
		}
		else if(key == 10){
			break;
		}
	} while(key != 'q' || key != 'Q');
	wclear(levelSelect);
	gameStart(1);
}

void draw(WINDOW *win){
	wattron(win, COLOR_PAIR(3));
	g.drawMap();
	wattroff(win, COLOR_PAIR(3));
	
	wattron(win, COLOR_PAIR(17));
	g.drawCharacter();
	wattroff(win, COLOR_PAIR(17));

	wattron(win, COLOR_PAIR(18));
	g.drawDestination();
	wattroff(win, COLOR_PAIR(18));

	wattron(win, COLOR_PAIR(15));
	g.drawBoxs();
	wattroff(win, COLOR_PAIR(15));
}
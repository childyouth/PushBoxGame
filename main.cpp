#include<ncurses.h>
#include "map.h"
#include "game.h"
#include "gameobject.h"
#define WIN_SIZE_Y 40
#define WIN_SIZE_X 50

void init_colors();
void handle_menu_cursor(int key, int &y); // 메인 메뉴에서 커서 이동
void select_this_menu(int y); // Enter입력으로 메뉴에 따른 아이템 실행
void show_pause_screen(WINDOW *win, string message="  Press Any KEY To\n      CONTINUE"); // P를 눌렀을 시 Pause
void gameStart(int prefix=0); // Main game loop로 들어감
void gameLoop();
void selectLevel();
void draw(WINDOW *); // gameObjects 놈들 draw

WINDOW *gamescreen, *pause, *levelSelect;
game g(gamescreen);
char temp[30];

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
	// echo();
	noecho();
	
	// 로비 띄우기
	int cursor_x=3, cursor_y=4;
	bool end = false;
	while(1){
		clear();
		attron(COLOR_PAIR(1));
		border('*','*','*','*','*','*','*','*');
		attroff(COLOR_PAIR(1));
		char c_y = (char)cursor_y + '0';
		attron(COLOR_PAIR(2));
		mvprintw(2, cursor_x, " PushBoxGame");
		mvprintw(cursor_y, cursor_x, ">");
		if(cursor_y == 4)
		attron(COLOR_PAIR(4));
		else attron(COLOR_PAIR(2));
		mvprintw(4, 4, "start game");
		if(cursor_y == 5)
		attron(COLOR_PAIR(4));
		else attron(COLOR_PAIR(2));
		mvprintw(5, 4, "Choose Level");
		attroff(COLOR_PAIR(4));
		
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
	init_pair(4, COLOR_RED, COLOR_WHITE); // selected char color

	init_pair(9, COLOR_BLACK, COLOR_BLACK); // gaem screen color
	init_pair(10, COLOR_WHITE, COLOR_WHITE); // background color
	init_pair(11, COLOR_RED, COLOR_RED); // pause background color

	init_pair(15, COLOR_GREEN, COLOR_BLACK); // box color
	init_pair(16, COLOR_YELLOW, COLOR_BLACK); // complete box color
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
void show_pause_screen(WINDOW *win, string message){
	wbkgd(pause,COLOR_PAIR(11));
	wattron(pause,COLOR_PAIR(21));
	mvwprintw(pause,1,1,message.c_str());
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
// 게임 로비에서 항상 출력되어야 하는 기본 세팅들
void lobbyFixedString(){ 
	wattron(gamescreen,COLOR_PAIR(1));
	wborder(gamescreen,'0','0','0','0','0','0','0','0');
	wattroff(gamescreen,COLOR_PAIR(1));
	wattron(gamescreen, COLOR_PAIR(3));
	sprintf(temp, "%d", g.getLevel()); // int -> string
	mvwprintw(gamescreen, 1, 3, "Hurry UP! ");
	mvwprintw(gamescreen, 2, 3, "Level : ");
	mvwprintw(gamescreen, 2, 11, temp);
	sprintf(temp,"    move : %d",0);
	mvwprintw(gamescreen,1,16,temp);
	sprintf(temp, "box move : %d", g.box_move_cnt);
	mvwprintw(gamescreen, 2, 16, temp);
	mvwprintw(gamescreen, 1, 30, "quit : q or Q");
	wattroff(gamescreen, COLOR_PAIR(3));
	wattroff(gamescreen, COLOR_PAIR(3));
}

void gameStart(int prefix){
	g.setWindow(gamescreen);

	wbkgd(gamescreen,COLOR_PAIR(9));
	int level = 0;
	while(!g.isGameEnd()){
		// prefix가 1일 시 levelselect를 통해서 온 것이므로 newStage가 불필요
		if(!prefix) g.newStage(level++);
		// 게임 기본 세팅, 윈도우 생성, 맵 그리기
		lobbyFixedString();
		draw(gamescreen);
		
		wrefresh(gamescreen);
		
		// 메인 게임 루프실행
		gameLoop();
		show_pause_screen(gamescreen, "   Game Clear!!\n  Press Any KEY To\n      CONTINUE");
	}
}
void gameLoop(){
	int a =0;
	while(!g.isStageEnd()){
		GameObject *character = &g.getCharater();
		int key = getch();
		int move_cnt = g.move_cnt;
		int v = 0;
		switch(key){
			case KEY_LEFT:
				v = 4;break;
			case KEY_RIGHT:
				v = 3;break;
			case KEY_UP:
				v = 2;break;
			case KEY_DOWN:
				v = 1;break;
			case 'p':
				show_pause_screen(gamescreen);break;
			case 'q':
				g.endGame(); wclear(gamescreen); exit(1);
			case 'r':
				move_cnt = 0;
				g.move_cnt = 0;
				g.box_move_cnt=0;
				g.newStage(g.getLevel()); break; // 자신의 레벨로 초기화
		}
		wclear(gamescreen);
		lobbyFixedString();
		if(v != 0){
			if(character->move(v,1) != -1)
				move_cnt ++;
		}
		g.move_cnt = move_cnt;
		sprintf(temp,"    move : %d",move_cnt);
		
		draw(gamescreen);
		wattron(gamescreen, COLOR_PAIR(3));
		mvwprintw(gamescreen,1,16,temp);
		g.isBoxMoved();
		sprintf(temp, "box move : %d", g.box_move_cnt);
		mvwprintw(gamescreen, 2, 16, temp);
		
		mvwprintw(gamescreen, 1, 30, "quit : q or Q");

		wattroff(gamescreen, COLOR_PAIR(3));

		wrefresh(gamescreen);
	}
}
void selectLevel(){
	int key, level=0, maxLevel = g.getMapNum();

	g.setWindow(levelSelect);
	wbkgd(levelSelect,COLOR_PAIR(9));
	while(key != 'q' || key != 'Q' || key != 10){
		g.newStage(level);

		wattron(levelSelect,COLOR_PAIR(1));
		wborder(levelSelect,'0','0','0','0','0','0','0','0');
		wattroff(levelSelect,COLOR_PAIR(1));

		wattron(levelSelect, COLOR_PAIR(3));
		sprintf(temp, "Current Level %d", level); // int -> string
		mvwprintw(levelSelect, 2, 3, temp);
		wattroff(levelSelect, COLOR_PAIR(3));
		draw(levelSelect);

		wrefresh(levelSelect);
		key = getch();
		wclear(levelSelect);
		switch(key){
			case KEY_LEFT:
			case KEY_DOWN:
			if(level>0) level--;
			else mvwprintw(levelSelect, 2, 3, "This level is Min Level");
			break;
			case KEY_RIGHT:
			case KEY_UP:
			if(level<maxLevel-1) level++;
			else mvwprintw(levelSelect, 2, 3, "T his level is Max Level");
			break;
		}
		if(key == 10){
			break;
		}	
	}
	wclear(levelSelect);
	wrefresh(levelSelect);
	gameStart(1);
}

void draw(WINDOW *win){
	wattron(win, COLOR_PAIR(3));
	g.drawMap();
	wattroff(win, COLOR_PAIR(3));

	wattron(win, COLOR_PAIR(18));
	g.drawDestination();
	wattroff(win, COLOR_PAIR(18));

	wattron(win, COLOR_PAIR(15));
	g.drawBoxs();
	wattroff(win, COLOR_PAIR(15));

	wattron(win, COLOR_PAIR(16));
	g.drawCompleteBox();
	wattroff(win, COLOR_PAIR(16));

	wattron(win, COLOR_PAIR(17));
	g.drawCharacter();
	wattroff(win, COLOR_PAIR(17));
}

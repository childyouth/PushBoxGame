#include<ncurses.h>
#include "map.h"
#include "game.h"
#define WIN_SIZE_Y 18
#define WIN_SIZE_X 78

WINDOW *gamescreen, *pause;

void init_colors(){
	start_color();
	init_pair(1, COLOR_MAGENTA, COLOR_MAGENTA); // border color
	init_pair(2, COLOR_BLACK, COLOR_WHITE); // char color
	init_pair(3, COLOR_BLACK, COLOR_WHITE); // gaem screen color
	init_pair(4, COLOR_BLACK, COLOR_WHITE); // game screen char color

	init_pair(10, COLOR_WHITE, COLOR_WHITE); // background color
	init_pair(11, COLOR_RED, COLOR_RED); // pause background color

	init_pair(20, COLOR_BLACK, COLOR_BLACK); // string color
	init_pair(21, COLOR_BLUE, COLOR_RED); // pause string color
}

void show_pause_screen(WINDOW *pause){
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
	touchwin(stdscr);
}

void select_this_menu(int y){
	if(y == 4){
		game g(gamescreen);
		g.newGame();
		g.drawMap();
	}
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
		case 10:
			y+= 2;
			select_this_menu(y);
	}	
}
// switch(key){
// 			case KEY_LEFT:
// 				y--;break;
// 			case KEY_RIGHT:
// 				y++;break;
// 			case KEY_UP:
// 				x--;break;
// 			case KEY_DOWN:
// 				x++;break;
// 		}
int main(){
	initscr();

	gamescreen = newwin(WIN_SIZE_Y,WIN_SIZE_X,1,1);
	pause = newwin(6,20,WIN_SIZE_Y/2 - 3, WIN_SIZE_X/2 - 10);
	
	// 게임 기본 세팅
	init_colors();
	bkgd(COLOR_PAIR(10));

	resize_term(20,80);

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

#include<ncurses.h>

#define WIN_SIZE_Y 18
#define WIN_SIZE_X 78

int main(){
	initscr();

	WINDOW *lobby, *game, *menu;
	lobby = newwin(WIN_SIZE_Y,WIN_SIZE_X,1,1);
	game = newwin(WIN_SIZE_Y,WIN_SIZE_X,1,1);
	menu = newwin(6,20,WIN_SIZE_Y/2 - 3, WIN_SIZE_X/2 - 10);

	start_color();
	init_pair(1, COLOR_MAGENTA, COLOR_MAGENTA); // border color
	init_pair(2, COLOR_BLACK, COLOR_WHITE); // char color

	init_pair(10, COLOR_WHITE, COLOR_WHITE); // background color
	init_pair(11, COLOR_RED, COLOR_RED); // menu background color

	init_pair(20, COLOR_BLACK, COLOR_BLACK); // string color
	init_pair(21, COLOR_BLUE, COLOR_RED); // menu string color

	bkgd(COLOR_PAIR(10));

	resize_term(20,80);

	attron(COLOR_PAIR(1));
	border('0','0','0','0','0','0','0','0');
	attroff(COLOR_PAIR(1));
	int x=3,y=4;
	attron(COLOR_PAIR(2));
	mvprintw(x,y,"O");
	attroff(COLOR_PAIR(2));

	keypad(stdscr,TRUE);
	curs_set(0);
	noecho();

	int line = 4;
	bool end = false;
	while(!end){
		clear();
		attron(COLOR_PAIR(2));
		mvprintw(x,y,"0");
		attroff(COLOR_PAIR(2));
		refresh();
		int key = getch();
		switch(key){
			case ' ':
				end = true;
				break;
			case 'p':
			case 'P':
				wbkgd(menu,COLOR_PAIR(11));
				wattron(menu,COLOR_PAIR(21));
				mvwprintw(menu,1,1,"  Press Any KEY To\n      CONTINUE");
				wattroff(menu,COLOR_PAIR(21));
				wattron(menu,COLOR_PAIR(1));
				wborder(menu,'0','0','0','0','0','0','0','0');
				wattroff(menu,COLOR_PAIR(1));
				wrefresh(menu);
				getch();
				wclear(menu);
				wrefresh(menu);
				touchwin(stdscr);
				break;
			case KEY_LEFT:
				y--;break;
			case KEY_RIGHT:
				y++;break;
			case KEY_UP:
				x--;break;
			case KEY_DOWN:
				x++;break;
		}
	}

	refresh();
	getch();
	endwin();
	return 0;
}

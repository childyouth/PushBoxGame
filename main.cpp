#include<ncurses.h>
int main(){
	initscr();
	start_color();
	init_pair(1, COLOR_MAGENTA, COLOR_MAGENTA); // wall color
	init_pair(2, COLOR_BLACK, COLOR_WHITE); // char color
	init_pair(0, COLOR_WHITE, COLOR_WHITE); // background color

	bkgd(COLOR_PAIR(0));

	resize_term(10,50);

	attron(COLOR_PAIR(1));
	border('0','0','0','0','0','0','0','0');
	attroff(COLOR_PAIR(1));

	attron(COLOR_PAIR(2));
	mvprintw(3,4,"O");
	attroff(COLOR_PAIR(2));

	refresh();
	getch();
	endwin();
	return 0;
}

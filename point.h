#ifndef POINT_H
#define POINT_H

class point{
		friend class map;
		int col, row;
		point(){}
		point(int _col, int _row){col = _col; row=_row;}
};

#endif
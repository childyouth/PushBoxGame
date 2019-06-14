#ifndef POINT_H
#define POINT_H

class point{
    public:
		int col=0, row=0;
		point(){}
		point(int _col, int _row){col = _col; row=_row;}
		point(const point& p){col = p.col; row= p.row;}
		void setPoint(int _col, int _row){col = _col; row=_row;}
};

#endif
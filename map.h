#ifndef MAP_H
#define MAP_H

class map{
public:
	int col,row;
	int **m;
	map(int c,int r):col(c),row(r){
		**m = new int*[col];
		for(int i = 0;i<col;i++){
			m[i] = new int[row];
		}
	}
	void setMap(

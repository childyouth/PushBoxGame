#include "map.h"

map::map(int c, int r) : col(c), row(r) {
    m = new int *[col];
    for (int i = 0; i < col; i++) {
        m[i] = new int[row];
    }
}
void map::setMap(char filename[]) {
    ifstream reader(filename);
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            reader >> m[i][j];
        }
    }
}

void map::checkMapData(){
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}
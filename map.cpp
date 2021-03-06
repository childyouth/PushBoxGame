#include "map.h"
#include "gameobject.h"
#include <sstream>
// #include <algorithm>

void map::initMap()
{
    ifstream reader("maps.txt");
    string temp;
    getline(reader, temp);
    num_maps = atoi(temp.c_str());
    // cout << "맵 데이터의 수 : " << num_maps << endl;

    int c_col, c_row;   // 캐릭터 위치 정보
    char start_symbol;  // @

    chracters = new GameObject[num_maps]; // 캐릭터 위치 배열
    map_sizes = new point[num_maps]; // 맵 사이즈 배열
    // fill(chracters, chracters+num_maps, 0);
    // fill(map_sizes, map_sizes+num_maps, 0);
    vector<string> line;           // 줄별로 받아온 데이터
    
    for (int i = 0; i < num_maps; i++)
    {
        int row = 0, col = 0; // 맵 사이즈
        line = vector<string>(); // 벡터 초기화

        getline(reader, temp);
        c_col = temp[0] - '0';
        c_row = temp[2] - '0';
		chracters[i] = GameObject(point(c_col, c_row), 8, true);
        while (1) {
            getline(reader, temp);
            line.push_back(temp);
            if (line.back() == "@") { // 맵 구분자
                break;
            }
            // cout << line.back() << endl;
        }

        line.pop_back(); // 맵 구분자를 벡터에서 제거
        row = line.size(); // 줄 수
        col = line[0].size() / 2 + 1; // 공백 제거
        map_sizes[i] = point(col, row);

        // cout << "row : " << map_sizes[i].row << " col : " << map_sizes[i].col << endl;
        if(i==0){ // map 초기화
            maps.assign(num_maps, vector<vector<int> >(row, vector<int>()));
        }
        setMap(i, col, row, line);
    }
}

void map::setMap(int level, int col, int row, vector<string> temp) {
    string tempString;
    vector<vector<int> > &map = maps[level];
    for (int i = 0; i < temp.size(); i++)
    {
        for(int s=0; s<temp[i].size(); s++){
            if(temp[i][s] == ' ') continue;
            map[i].push_back(temp[i][s] - '0');
        }
        // for(int s=0; s<map[i].size(); s++){
        //     cout << map[i][s] << " ";
        // }
        // checkMapData(level);
        // cout << endl;
    }
    // checkMapData(level);
}

vector<vector<int> > map::getMap(int level)
{
    return maps[level];
}

GameObject map::getChracter(int level)
{
    return chracters[level];
}

point map::getMapSize(int level)
{
    return map_sizes[level];
}

int map::getMapNum()
{
    return num_maps;
}

void map::checkMapData(int level)
{
    vector<vector<int> > map = maps[level];
    point map_size = getMapSize(level);
    for (int row = 0; row < map_size.row; row++)
    {
        for (int col = 0; col < map_size.col; col++)
        {
            cout << map[row][col] << " ";
        }
        cout << endl;
    }
}

// int main()
// {
//     map m;
//     m.initMap();
//     int times = m.getMapNum();
//     for(int i=0; i<times; i++){
//         m.checkMapData(i);
//         cout << endl;
//     }
// }

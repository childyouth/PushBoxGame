#include "map.h"
#include <sstream>

void map::initMap()
{
    ifstream reader("maps.txt");
    string temp;
    getline(reader, temp);
    num_maps = atoi(temp.c_str());
    cout << "맵 데이터의 수 : " << num_maps << endl;

    int c_col, c_row;   // 캐릭터 위치 정보
    char start_symbol;  // @

    chracters = new point[num_maps]; // 캐릭터 위치 배열
    map_sizes = new point[num_maps]; // 맵 사이즈 배열
    vector<string> line;           // 줄별로 받아온 데이터
    
    for (int i = 0; i < num_maps; i++)
    {
        int row = 0, col = 0; // 맵 사이즈
        line = vector<string>(); // 벡터 초기화

        getline(reader, temp);
        c_col = temp[0];
        c_row = temp[2];
        chracters[i] = point(c_col, c_row);

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

        cout << "row : " << row << " col : " << col << endl;
        if(i==0){ // map 초기화
            maps.assign(num_maps, vector<vector<int> >(row, vector<int>(col, 0)));
        }
        setMap(i, col, row, line);
    }
}

void map::setMap(int level, int col, int row, vector<string> temp) {
    string tempString;
    vector<vector<int> > &map = maps[level];
    for (int i = 0; i < temp.size(); i++)
    {
        stringstream stream;
        stream.str(temp[i]);
        int idx = 0;
        while(stream >> tempString){
            if (tempString != " ") {
                int n = atoi(tempString.c_str());
                map[i][idx] = n;
                idx++;
            }
        }
    }
}

vector<vector<int> > map::getMap(int level)
{
    return maps[level];
}

point map::getChracter(int level)
{
    return map_sizes[level];
}

point map::getMapSize(int level)
{
    return chracters[level];
}

int map::getMapNum()
{
    return num_maps;
}

void map::checkMapData(int level)
{
    vector<vector<int> > map = maps[level];
    point map_size = map_sizes[level];
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
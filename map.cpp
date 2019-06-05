#include "map.h"

void map::initMap()
{
    ifstream reader("maps.txt");
    string temp;
    getline(reader, temp);
    num_maps = temp[0] - '0'; // 맵의 개수
    int c_col, c_row;   // 캐릭터 위치 정보
    char start_symbol;  // @

    maps = new int **[num_maps];
    chracters = new Point[num_maps]; // 캐릭터 위치 배열
    map_sizes = new Point[num_maps]; // 맵 사이즈 배열
    string line[MAX_LINE];           // 줄별로 받아온 데이터

    for (int i = 0; i < num_maps; i++)
    {
        int row = 0, col = 0; // 맵 사이즈

        getline(reader, temp);
        c_col = temp[0];
        c_row = temp[2];
        chracters[i] = Point(c_col, c_row);

        while (1)
        {
            getline(reader, line[row]);
            if (line[row] == "@")
            { // 맵 구분자
                break;
            }
            cout << line[row] << endl;
            row++;
        }

        col = line[0].size() / 2 + 1; // 공백 제거
        map_sizes[i] = Point(col, row);
        cout << "row : " << row << " col : " << col << endl;

        setMap(i, col, row, line);
    }
}

void map::setMap(int level, int col, int row, string *temp)
{
    maps[level] = new int *[row]; // 단일 맵 데이터
    // 맵을 temp값을 해석해서 저장
    for (int i = 0; i < row; i++)
    {
        maps[level][i] = new int[col];
        cout << temp[i] << endl;
        for (int j = 0; j < temp[i].size(); j++)
        {
            cout << j << endl;
            if (temp[i][j] != ' ')
            {
                int n = temp[i][j] - '0';
                maps[level][i][j] = n;
            }
        }
        cout << endl;
    }
}

int **map::getMap(int level)
{
    return maps[level];
}

Point map::getChracter(int level)
{
    return map_sizes[level];
}

Point map::getMapSize(int level)
{
    return chracters[level];
}

int map::getMapNum()
{
    return num_maps;
}

void map::checkMapData(int level)
{
    int **map = maps[level];
    Point map_size = map_sizes[level];
    for (int row = 0; row < map_size.row-1; row++)
    {
        for (int col = 0; col < map_size.col-1; col++)
        {
            cout << map[row][col] << " ";
        }
        cout << endl;
    }
}

int main()
{
    map m;
    m.initMap();
}
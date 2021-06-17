#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

const int HEIGHT = 25;
const int WIDTH = 25;
const int STEP_MAX = 4;

class MapManager {
  vector<vector<vector<int>>> total_map;
  vector<vector<int>> map;

  void make_all_map();
  string get_map_url(int step);

public:
  MapManager();
  vector<vector<int>> get_map();
  void open_map(int step); // step : 0~3 총 4개
};

MapManager::MapManager() {
  total_map.assign(STEP_MAX, vector<vector<int>>(HEIGHT, vector<int>(WIDTH, 0)));
  map.assign(HEIGHT, vector<int> (WIDTH, 0));
  make_all_map();
  open_map(0);
}

void MapManager::make_all_map() {
  for (int step=0; step<STEP_MAX; step++) {
    ifstream read(get_map_url(step+1));

    int idx = 0;
    string temp;

    while (read.peek() != EOF) {
      getline(read, temp);
      for (int i=0; i<WIDTH; i++)
        total_map[step][idx][i] = temp[i] - '0';
      idx++;
    }
  }
}

string MapManager::get_map_url(int step) { //step 1~4
  return "./map_data/map_sample" + to_string(step) + ".txt";
}

void MapManager::open_map(int step) {
  map = total_map[step];
}

vector<vector<int>> MapManager::get_map() {
  return map;
}

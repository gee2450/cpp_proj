#ifndef __MAP__INCLUDED__
#define __MAP__INCLUDED__

#include <fstream>
#include <vector>
#include <iostream>

const int HEIGHT = 25;
const int WIDTH = 25;
const int STEP_MAX = 4;

class MapManager {
  std::vector<std::vector<std::vector<int>>> total_map;
  std::vector<std::vector<int>> map;

  void make_all_map();
  std::string get_map_url(int step);

public:
  MapManager();
  std::vector<std::vector<int>> get_map();
  void open_map(int step); // step : 0~3 총 4개
};

#endif

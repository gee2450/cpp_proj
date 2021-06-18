#include "Edit_Data.h"

using namespace std;

Edit_Data::Edit_Data(vector<vector<int>> map) {
  this->map = map;
}

void Edit_Data::edit(int x, int y, int item) {
  map[y][x] = item;
}

int Edit_Data::get(int x, int y) {
  return map[y][x];
}

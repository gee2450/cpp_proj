#ifndef __EDIT_DATA__INCLUDED__
#define __EDIT_DATA__INCLUDED__

#include <iostream>
#include <vector>

class Edit_Data {
  std::vector<std::vector<int>> map;
public:
  Edit_Data(std::vector<std::vector<int>> map);
  void edit(int x, int y, int item);
  int get(int x, int y);
};

#endif

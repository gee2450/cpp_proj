#ifndef __ITEM__INCLUDED__
#define __ITEM__INCLUDED__

#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

class Edit_Data;

class Item {
  WINDOW* win;
  Edit_Data* map_proc;
  clock_t* timer;
  std::vector<std::vector<int>> position;
public:
  Item(WINDOW& win, Edit_Data& map_proc);
  void item_manager();
  void new_item(int idx);
  bool check_item(int idx);
};

#endif

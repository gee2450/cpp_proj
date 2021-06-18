#ifndef __SNAKE__INCLUDED__
#define __SNAKE__INCLUDED__

#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <deque>

class Edit_Data;

class Snake {
  int step;
  std::deque<std::deque<int>> s_body;
  std::deque<int> start;
  std::string state;
  WINDOW* win;
  std::vector<std::vector<int>> origin_map;
  Edit_Data* map_proc;
  Score* score;
  Mission* mission;
  bool test_add = false;
public:
  bool* flag;
  Snake(int step, bool& flag, WINDOW& win,
        std::vector<std::vector<int>>& origin_map,
        Edit_Data& map_proc, Score& score, Mission& mission);
  void position();
  void get_key();
  bool pass();
  void fail();
};

#endif

#ifndef __SCORE_MISSION__INCLUDED__
#define __SCORE_MISSION__INCLUDED__

#include <ncurses.h>
#include <iostream>
#include <vector>

class Score {
  int current_length;
  int max_length;
  int growth_items;
  int poison_items;
  int gate_cnt;
  WINDOW* win;
  friend class Mission;
public:
  Score() {;}
  Score(WINDOW& xwin);
  void update();
  void plus_current_length() { current_length++; }
  void minus_current_length() { current_length--; }
  void check_max_length() { if (current_length>max_length) max_length = current_length; }
  void plus_growth_items() { growth_items++; }
  void plus_poison_items() { poison_items++; }
  void plus_gate_cnt() { gate_cnt++; }
};

class Mission {
  int length;
  int growth_items;
  int poison_items;
  int gate_cnt;
  Score* score;
  bool length_check;
  bool growth_items_check;
  bool poison_items_check;
  bool gate_cnt_check;
  WINDOW* win;
  void check();
public:
  Mission(WINDOW&, int, int, int, int, Score&);
  void update();
  bool pass();
};

#endif

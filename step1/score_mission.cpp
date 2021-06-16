#include <ncurses.h>
#include <iostream>
#include <vector>

using namespace std;

class Score {
  int current_length;
  int max_length;
  int growth_items;
  int poison_items;
  int gate_cnt;
  WINDOW* win;
  friend class Mission;
public:
  Score(WINDOW& xwin);
  WINDOW& update();
  void plus_current_length();
  void minus_current_length();
  void plus_max_length();
  void plus_growth_items();
  void plus_poison_items();
  void plus_gate_cnt();
};

Score::Score(WINDOW& xwin) {
  current_length = 0;
  max_length = 0;
  growth_items = 0;
  poison_items = 0;
  gate_cnt = 0;
  win = &xwin;
  box(win, 0, 0);
}
WINDOW& Score::update() {
  string ret;

  mvwprintw(win, 1, 1, "Score Board");
  ret = "B: " + to_string(current_length) + "/" + to_string(max_length);
  mvwprintw(win, 2, 1, ret.c_str() );
  ret = "+: " + to_string(growth_items);
  mvwprintw(win, 3, 1, ret.c_str());
  ret = "-: " + to_string(poison_items);
  mvwprintw(win, 4, 1, ret.c_str());
  ret = "G: " + to_string(gate_cnt);
  mvwprintw(win, 5, 1, ret.c_str());
  touchwin(win);
  wrefresh(win);

  return *win;
}

class Mission {
  int length;
  int growth_items;
  int poison_items;
  int gate_cnt;
  bool length_check;
  bool growth_items_check;
  bool poison_items_check;
  bool gate_cnt_check;
  WINDOW* win;
public:
  Mission(WINDOW&, int, int, int, int);
  WINDOW& update();
  void check(Score& score);
};

Mission::Mission( WINDOW& xwin, int length, int growth_items,
                  int poison_items, int gate_cnt) {
  this->length = length;
  this->growth_items = growth_items;
  this->poison_items = poison_items;
  this->gate_cnt = gate_cnt;
  length_check = false;
  growth_items_check = false;
  poison_items_check = false;
  gate_cnt_check = false;
  win = &xwin;
  box(win, 0, 0);
}
WINDOW& Mission::update() {
  string ret;

  mvwprintw(win, 1, 1, "Mission");
  ret = "B: " + to_string(length) + " (" + ((length_check) ? "V)" : " )");
  mvwprintw(win, 2, 1, ret.c_str() );
  ret = "+: " + to_string(growth_items) + " (" + ((growth_items_check) ? "V)" : " )");
  mvwprintw(win, 3, 1, ret.c_str());
  ret = "-: " + to_string(poison_items) + " (" + ((poison_items_check) ? "V)" : " )");
  mvwprintw(win, 4, 1, ret.c_str());
  ret = "G: " + to_string(gate_cnt) + " (" + ((gate_cnt_check) ? "V)" : " )");
  mvwprintw(win, 5, 1, ret.c_str());
  touchwin(win);
  wrefresh(win);

  return *win;
}

void Mission::check(Score& score) {
  length_check = (score.max_length >= length) ? true : false;
  growth_items_check = (score.growth_items >= growth_items) ? true : false;
  poison_items_check = (score.poison_items <= poison_items) ? true : false;
  gate_cnt_check = (score.gate_cnt >= gate_cnt) ? true : false;
}

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
public:
  Score(WINDOW& xwin);
  WINDOW& update();
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
  mvwprintw(win, 1, 1, "Score Board");
  string ret = "B: " + to_string(current_length) + "/" + to_string(max_length);
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
  WINDOW* win;
public:
  Mission(WINDOW&, int, int, int, int);
  WINDOW& update();
};

Mission::Mission( WINDOW& xwin, int length, int growth_items,
                  int poison_items, int gate_cnt) {
  this->length = length;
  this->growth_items = growth_items;
  this->poison_items = poison_items;
  this->gate_cnt = gate_cnt;
  win = &xwin;
  box(win, 0, 0);
}
WINDOW& Mission::update() {
  mvwprintw(win, 1, 1, "Mission");
  string ret = "B: " + to_string(length);
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

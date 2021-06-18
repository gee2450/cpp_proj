#include "score_mission.h"

using namespace std;

Score::Score(WINDOW& xwin) {
  current_length = 3;
  max_length = 3;
  growth_items = 0;
  poison_items = 0;
  gate_cnt = 0;
  win = &xwin;
  box(win, 0, 0);
}
void Score::update() {
  string ret;

  mvwprintw(win, 1, 1, "Score Board");
  ret = "B: " + to_string(current_length) + "/" + to_string(max_length) + ' ';
  mvwprintw(win, 2, 1, ret.c_str() );
  ret = "+: " + to_string(growth_items) + ' ';
  mvwprintw(win, 3, 1, ret.c_str());
  ret = "-: " + to_string(poison_items) + ' ';
  mvwprintw(win, 4, 1, ret.c_str());
  ret = "G: " + to_string(gate_cnt) + ' ';
  mvwprintw(win, 5, 1, ret.c_str());

  touchwin(win);
  wrefresh(win);
}

Mission::Mission( WINDOW& xwin, int length, int growth_items,
                  int poison_items, int gate_cnt, Score& score) {
  this->length = length;
  this->growth_items = growth_items;
  this->poison_items = poison_items;
  this->gate_cnt = gate_cnt;
  this->score = &score;
  length_check = false;
  growth_items_check = false;
  poison_items_check = false;
  gate_cnt_check = false;
  win = &xwin;
  box(win, 0, 0);
}
void Mission::update() {
  string ret;

  check();

  mvwprintw(win, 1, 1, "Mission");
  if (length_check == true) ret = "B: " + to_string(length) + " (V) ";
  else                      ret = "B: " + to_string(length) + " ( ) ";
  mvwprintw(win, 2, 1, ret.c_str() );
  if (growth_items_check == true) ret = "+: " + to_string(growth_items) + " (V) ";
  else                            ret = "+: " + to_string(growth_items) + " ( ) ";
  mvwprintw(win, 3, 1, ret.c_str());
  if (poison_items_check == true) ret = "-: " + to_string(poison_items) + " (V) ";
  else                            ret = "-: " + to_string(poison_items) + " ( ) ";
  mvwprintw(win, 4, 1, ret.c_str());
  if (gate_cnt_check == true) ret = "G: " + to_string(gate_cnt) + " (V) ";
  else                        ret = "G: " + to_string(gate_cnt) + " ( ) ";
  mvwprintw(win, 5, 1, ret.c_str());

  touchwin(win);
  wrefresh(win);
}

void Mission::check() {
  if (score->max_length >= length) length_check = true;
  if (score->growth_items >= growth_items) growth_items_check = true;
  if (score->poison_items >= poison_items) poison_items_check = true;
  if (score->gate_cnt >= gate_cnt) gate_cnt_check = true;
}

bool Mission::pass() {
  if (length_check==true && growth_items_check==true &&
      poison_items_check==true && gate_cnt_check == true) {
    getch();
    return true;
  }
  return false;
}

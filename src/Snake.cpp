#include "score_mission.h"
#include "Snake.h"
#include "Edit_Data.h"

using namespace std;

Snake::Snake(int step, bool& flag, WINDOW& win,
             vector<vector<int>>& origin_map,
             Edit_Data& map_proc, Score& score, Mission& mission)
{
  this->step = step;
  this->win = &win;
  this->origin_map = origin_map;
  this->map_proc = &map_proc;
  this->score = &score;
  this->mission = &mission;
  state = "left";
  this->flag = &flag;
  test_add = false;

  keypad(stdscr, TRUE);

  // snake 머리 위치 설정
  if (step==0)
    start = deque<int>(12, 11);
  else if (step==1)
    start = deque<int>(7, 17);
  else if (step==2)
    start = deque<int>(11, 11);
  else if (step==3)
    start = deque<int>(11, 11);

  deque<int> ret;
  ret.push_back(start[0]+1); ret.push_back(start[1]);
  s_body.push_back(ret);
  ret.clear();
  ret.push_back(start[0]+2); ret.push_back(start[1]);
  s_body.push_back(ret);

  this->map_proc->edit(start[0],   start[0], 3);
  this->map_proc->edit(start[0]+1, start[0], 4);
  this->map_proc->edit(start[0]+2, start[0], 4);

  // snake window에 표시
  mvwprintw(this->win, start[1]+1, start[0]+1, to_string(3).c_str());
  mvwprintw(this->win, start[1]+1, start[0]+2, to_string(4).c_str());
  mvwprintw(this->win, start[1]+1, start[0]+3, to_string(4).c_str());

  touchwin(this->win);
  wrefresh(this->win);

  getch();
}

void Snake::position() {
  // 머리를 body에 집어넣음
  map_proc->edit(start[0], start[1], 4);
  mvwprintw(win, start[1]+1, start[0]+1, to_string(4).c_str());
  s_body.push_front(start);

  // 머리 이동
  if (state == "left") start[0]--;
  else if (state == "right") start[0]++;
  else if (state == "up") start[1]--;
  else if (state == "down") start[1]++;
  mvwprintw(win, start[1]+1, start[0]+1, to_string(3).c_str());

  // 머리가 향하는 방향에 있는 것 판단
  int ret = map_proc->get(start[0], start[1]);
  if (ret == 5) { // growth
    score->plus_current_length();
    score->check_max_length();
    score->plus_growth_items();

    score->update();
    mission->update();

    test_add = true;
  }
  else if (ret == 6) { // poison
    score->minus_current_length();
    score->plus_poison_items();

    score->update();
    mission->update();

    // tail 없앰 -> 뱀 크기 줄어듬
    map_proc->edit(s_body.back()[0], s_body.back()[1], 0);
    mvwprintw(win, s_body.back()[1]+1, s_body.back()[0]+1, to_string(0).c_str());
    s_body.pop_back();
  }
  else if (ret != 0) { // body
    *flag = false;
    fail();
  }

  // fail 아니면 머리 위치 갱신
  map_proc->edit(start[0], start[1], 3);

  // tail 없앰 (이동 구현 위해)
  if (test_add == false) {
    map_proc->edit(s_body.back()[0], s_body.back()[1], 0);
    mvwprintw(win, s_body.back()[1]+1, s_body.back()[0]+1, to_string(0).c_str());
    s_body.pop_back();
  }
  test_add = false;

  touchwin(win);
  wrefresh(win);

  // 만약 뱀 길이가 3보다 작으면 종료
  if (s_body.size()<2) {
    *flag = false;
    fail();
  }
}

void Snake::get_key() {
  int key;

  key = getch();
  if (key == KEY_LEFT)
    if (state == "right") *flag = false;
    else state = "left";
  else if (key == KEY_RIGHT)
    if (state == "left")  *flag = false;
    else state = "right";
  else if (key == KEY_UP)
    if (state == "down")  *flag = false;
    else state = "up";
  else if (key ==KEY_DOWN)
    if (state == "up")    *flag = false;
    else state = "down";

  else if (key =='f')
    *flag = false;
}

void Snake::fail() {
  *flag = false;
  getch();
  werase(win);
  string ret = "You Fail";
  mvwprintw(win, 13, 8, ret.c_str());
  touchwin(win);
  wrefresh(win);
  getch();
  exit(0);
}

bool Snake::pass() {
  return mission->pass();
}

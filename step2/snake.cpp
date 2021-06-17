#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <deque>

using namespace std;

class Snake {
  int step;
  deque<deque<int>> s_body;
  deque<int> start;
  string state;
  WINDOW* win;
  vector<vector<int>> origin_map;
  vector<vector<int>> map;
  bool test_add = false;
public:
  bool* flag;
  Snake(int step, bool& flag, WINDOW& win,
        vector<vector<int>>& origin_map, vector<vector<int>>& map);
  void position();
  void get_key();
  bool length_rule();
};

Snake::Snake(int step, bool& flag, WINDOW& win,
             vector<vector<int>>& origin_map, vector<vector<int>>& map)
{
  this->step = step;
  this->win = &win;
  this->map = map;
  this->origin_map = origin_map;
  state = "left";
  this->flag = &flag;

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
  map[start[0]][start[1]] = 3;
  map[start[0]+1][start[1]] = 4;
  map[start[0]+2][start[1]] = 4;

  // snake window에 표시
  mvwprintw(this->win, start[1]+1, start[0]+1, to_string(3).c_str());
  mvwprintw(this->win, start[1]+1, start[0]+2, to_string(4).c_str());
  mvwprintw(this->win, start[1]+1, start[0]+3, to_string(4).c_str());

  touchwin(this->win);
  wrefresh(this->win);

  getch();
}

void Snake::position() {
  // 머리 부분 3->4로 바꿈. 즉 머리를 body에 집어넣음
  map[start[0]][start[1]] = 4;
  mvwprintw(win, start[1]+1, start[0]+1, to_string(4).c_str());
  s_body.push_front(start);

  // add 시험용 코드입니다.
  if (test_add) { test_add = false; }

  // tail 없애고, 원래 상태로 복귀
  else {
    map[s_body.back()[0]][s_body.back()[1]] = origin_map[s_body.back()[0]][s_body.back()[1]];
    mvwprintw(win, s_body.back()[1]+1, s_body.back()[0]+1, to_string(0).c_str());
    s_body.pop_back();
  }

  if (state == "left") start[0]--;
  else if (state == "right") start[0]++;
  else if (state == "up") start[1]--;
  else if (state == "down") start[1]++;

  // 머리 이동
  mvwprintw(win, start[1]+1, start[0]+1, to_string(3).c_str());
  touchwin(win);
  wrefresh(win);

  if (map[start[0]][start[1]] == 5) {
    // growth
    test_add = true;
  }
  else if (map[start[0]][start[1]] == 6) {
    // poison
  }
  else if (map[start[0]][start[1]] != 0) {
    *flag = false;
    get_key();
  }

  // 만약 뱀 길이가 3보다 작으면 종료
  if (length_rule()==false) {
    *flag = false;
    get_key();
  }
}

bool Snake::length_rule() {
  if (s_body.size()<2) return false;
  return true;
}

void Snake::get_key() {
  int key;

  key = getch();
  if (key==KEY_LEFT)
    if (state == "right") *flag = false;
    else state = "left";
  else if (key==KEY_RIGHT)
    if (state == "left") *flag = false;
    else state = "right";
  else if (key==KEY_UP)
    if (state == "down") *flag = false;
    else state = "up";
  else if (key==KEY_DOWN)
    if (state == "up") *flag = false;
    else state = "down";
  else if (key=='f')
    *flag = false;

  else if (key=='a')
    test_add = true;

}

#include "MapManager.h"
#include "score_mission.h"
#include "Edit_Data.h"
#include "Snake.h"
#include "Item.h"

#include <ncurses.h>
#include <iostream>
#include <vector>
#include <thread>

using namespace std;
using namespace std::chrono;

int step = 0;

bool flag = true;

void Snake_Thread(Snake* s) {
  while (flag == true) {
    s->position();
    this_thread::sleep_for(milliseconds(500));
  }
}

int main() {
  MapManager a;

  a.open_map(step);
  vector<vector<int>> data = a.get_map();

  int b_mission[4] = {7, 10, 12, 15};
  int plus_mission[4] = {5, 10, 20, 30};
  int minus_mission[4] = {2, 5, 10, 20};
  int g_mission[4] = {0, 0, 0, 0}; // 제가 gate를 구현하지 못해서 0으로 고정시켰습니다.

  WINDOW* main_win = initscr();
  resize_term(33,55);
  box(main_win, 0, 0);
  refresh();

  WINDOW* win1;
  WINDOW* win2;
  WINDOW* win3;
  WINDOW* win4;

  win1 = newwin(27, 27, 3, 3);
  win2 = newwin(7, 20, 3, 32);
  win3 = newwin(7, 20, 10, 32);
  win4 = newwin(7, 20, 17, 32);

  box(win1, 0, 0);
  for (int i=0; i<25; i++) {
    for (int k=0; k<25; k++)
      mvwprintw(win1, i+1, k+1, to_string(data[i][k]).c_str());
  }
  touchwin(win1);
  wrefresh(win1);

  box(win4, 0, 0);
  string ret = "Press any keyboard";
  mvwprintw(win4, 1, 1, ret.c_str());
  ret = "Step : " + to_string(step+1);
  mvwprintw(win4, 2, 1, ret.c_str());
  ret = "Button : ";
  mvwprintw(win4, 3, 1, ret.c_str());
  ret = "  directional key";
  mvwprintw(win4, 4, 1, ret.c_str());
  touchwin(win4);
  wrefresh(win4);

  Score myScore(*win2);
  Mission myMission(*win3, b_mission[step], plus_mission[step],
                    minus_mission[step], g_mission[step], myScore);

  myScore.update();
  myMission.update();

  Edit_Data map_proc(data);
  Item item(*win1, map_proc);
  Snake snake(step, flag, *win1, data, map_proc, myScore, myMission);

  thread t1(Snake_Thread, &snake);
  thread t2(&Item::item_manager, &item);

  while (flag == true) {
    snake.get_key();

    if (snake.pass()) {
      werase(win1);
      string ret = "You WIN";
      mvwprintw(win1, 13, 8, ret.c_str());
      getch();
    }
  }

  delwin(win1);
  delwin(win2);
  delwin(win3);
  endwin();

  return 0;
}

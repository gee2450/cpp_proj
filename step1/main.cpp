#include "MapManager.cpp"
#include "score_mission.cpp"

#include <ncurses.h>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  MapManager a;
  a.open_map(1);
  vector<vector<int>> data = a.get_map();

  int b_mission = 10;
  int plus_mission = 5;
  int minus_mission = 2;
  int g_mission = 1;

  WINDOW* main_win = initscr();
  resize_term(33,55);
  box(main_win, 0, 0);
  refresh();

  WINDOW* win1;
  WINDOW* win2;
  WINDOW* win3;

  win1 = newwin(27, 27, 3, 3);
  box(win1, 0, 0);
  for (int i=0; i<25; i++) {
    for (int k=0; k<25; k++)
      mvwprintw(win1, i+1, k+1, to_string(data[i][k]).c_str());
  }
  touchwin(win1);
  wrefresh(win1);

  win2 = newwin(7, 20, 3, 32);
  Score myScore(*win2);
  myScore.update();

  win3 = newwin(7, 20, 10, 32);
  Mission myMission(*win3, b_mission, plus_mission, minus_mission, g_mission);
  myMission.update();

  getch();
  delwin(win1);
  delwin(win2);
  delwin(win3);
  endwin();

  return 0;
}

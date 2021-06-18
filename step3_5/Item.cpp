#include "Item.h"
#include "Edit_Data.h"

using namespace std;

#define TIMEOUT 7

Item::Item(WINDOW& win, Edit_Data& map_proc) {
  this->win = &win;
  this->map_proc = &map_proc;
  for (int i=0; i<3; i++) {
    vector<int> ret;
    ret.push_back(-1); ret.push_back(-1);
    position.push_back(ret);
  }
  srand((unsigned int)time(NULL));
  timer = new clock_t[3];
}

void Item::new_item(int idx) {
  if (position[idx][0] != -1)
    mvwprintw(win, position[idx][1]+1, position[idx][0]+1, to_string(0).c_str());

  srand((unsigned int)time(NULL));
  while (true) {
    int x = 1 + rand()%23; // 1~23
    int y = 1 + rand()%23;

    if (map_proc->get(x, y) != 0) continue;

    position[idx][0] = x; position[idx][1] = y;
    timer[idx] = time(NULL);

    int ret = (rand()%2) + 5;
    map_proc->edit(position[idx][0], position[idx][1], ret);
    mvwprintw(win, position[idx][1]+1, position[idx][0]+1, to_string(ret).c_str());
    touchwin(win);
    wrefresh(win);

    break;
  }
}

bool Item::check_item(int idx) {
  if (map_proc->get(position[idx][0], position[idx][1]) == 0) return false;
  return true;
}

void Item::item_manager() {
  for (int i=0; i<3; i++) {
    new_item(i);
  }

  while (true) {
    for (int i=0; i<3; i++) {
      if (check_item(i) == false) new_item(i);
      else if (time(NULL) - timer[i] >= TIMEOUT) new_item(i);
    }
  }
}

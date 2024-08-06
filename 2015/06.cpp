#include <algorithm>
#include <iostream>
#include <istream>
#include <string>
#include <utility>
#include <vector>

#define SIZE 1000

std::pair<int, int> read_coords(std::istream &in) {
  std::string s;
  in >> s;
  int p = s.find(",");
  int x = std::stoi(s.substr(0, p));
  int y = std::stoi(s.substr(p + 1));
  return std::make_pair(x, y);
}

std::pair<std::pair<int,int>,std::pair<int,int>> read_rect(std::istream &in){
  std::pair<int, int> beg, end;
  beg = read_coords(in);
  std::string tmp; in >> tmp;
  end = read_coords(in);
  return std::make_pair(beg, end);
}

int get_id(std::pair<int, int> coords) {
  return coords.second * SIZE + coords.first;
}

void set_lights_to(std::vector<int> &grid, std::pair<int, int> ul,
                   std::pair<int, int> dr, int on) {
  auto [begx, begy] = ul;
  auto [endx, endy] = dr;
  for (int i = begx; i <= endx; i++) {
    for (int j = begy; j <= endy; j++) {
      auto id = get_id({i, j});
      grid[id] = std::max(grid[id]+on, 0);
    }
  }
}

void toggle_lights(std::vector<int> &grid, std::pair<int, int> ul,
                   std::pair<int, int> dr) {
  auto [begx, begy] = ul;
  auto [endx, endy] = dr;
  for (int i = begx; i <= endx; i++) {
    for (int j = begy; j <= endy; j++) {
      int id = get_id(std::make_pair(i, j));
      grid[id] += 2;
    }
  }
}

int main() {
  std::string command;
  std::vector<int> grid (SIZE*SIZE, 0);
  
  while (std::cin >> command) {
    if (command == "turn") {
      std::cin >> command;
      int on = (command == "on") ? 1 : -1;
      auto [beg,end] = read_rect(std::cin);
      set_lights_to(grid, beg, end, on);
    } else if (command == "toggle") {
      auto [beg,end] = read_rect(std::cin);
      toggle_lights(grid, beg, end);
    }
  }
  
  int count = 0;
  for(auto l: grid){
    count += l;
  }
  std::cout << count << std::endl;
  return 0;
}

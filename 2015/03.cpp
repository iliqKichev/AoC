#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>

uint32_t make_hash(uint16_t x, uint16_t y) {
  uint32_t key = UINT32_MAX;
  key &= x;
  key <<= 16;
  key += y;
  return key;
}

std::pair<uint16_t, uint16_t> make_move(char el,
                                        std::pair<uint16_t, uint16_t> pos) {
  auto [x, y] = pos;
  switch (el) {
  case '^': {
    y--;
  } break;
  case 'v': {
    y++;
  } break;
  case '>': {
    x++;
  } break;
  case '<': {
    x--;
  } break;
  }
  return std::make_pair(x, y);
}

int main() {
  std::unordered_set<uint32_t> houses_onlySanta, houses_santaAndRobot;
  std::pair<uint16_t,uint16_t> pos_onlySanta = {0,0}, pos_santa = {0,0}, pos_robot = {0,0};
  bool isSanta = true;

  houses_onlySanta.insert(make_hash(0, 0));
  houses_santaAndRobot.insert(make_hash(0, 0));

  std::string in;
  std::cin >> in;

  for (auto el : in) {
    pos_onlySanta = make_move(el, pos_onlySanta);
    houses_onlySanta.insert(make_hash(pos_onlySanta.first, pos_onlySanta.second));
    if(isSanta){
      pos_santa = make_move(el, pos_santa);
      houses_santaAndRobot.insert(make_hash(pos_santa.first, pos_santa.second));
      isSanta = false;
    }
    else{
      pos_robot = make_move(el, pos_robot);
      houses_santaAndRobot.insert(make_hash(pos_robot.first, pos_robot.second));
      isSanta = true;
    }
  }
  std::cout << houses_onlySanta.size() << " Only Santa" << std::endl;
  std::cout << houses_santaAndRobot.size() << " With robots" << std::endl;

  return 0;
}


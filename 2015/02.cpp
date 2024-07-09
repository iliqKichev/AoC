#include <iostream>
#include <ostream>
#include <string>

int main() {
  int total_area = 0, total_length = 0;
  int sides[3], min_area, min_length, volume, index, pos_beg, pos_end;
  std::string in;
  while (std::cin >> in) {
    index = 0;
    pos_beg = 0;
    min_area = min_length = 1 << 20;
    volume = 1;

    while ((pos_end = in.find("x", pos_beg)) != std::string::npos) {
      sides[index] = std::stoi(in.substr(pos_beg, pos_end));
      pos_beg = pos_end + 1;
      index++;
    }
    sides[index] = std::stoi(in.substr(pos_beg, pos_end));

    for (int area, i = 0; i < 3; i++) {
      area = sides[i] * sides[(i + 1) % 3];
      min_area = std::min(min_area, area);
      total_area += 2 * area;
      volume *= sides[i];
      min_length = std::min(min_length, 2 * (sides[i] + sides[(i + 1) % 3]));
    }
    total_area += min_area;
    total_length += min_length + volume;
  }

  std::cout << total_area << std::endl;
  std::cout << total_length << std::endl;
  return 0;
}

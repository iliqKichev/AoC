#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::string> split(std::string s, std::string sep) {
  int pos = s.find(sep), oldpos = 0;
  std::vector<std::string> ans;
  while (pos != std::string::npos) {
    ans.push_back(s.substr(oldpos, pos - oldpos));
    oldpos = pos + 1;
    pos = s.find(sep, pos + 1);
  }
  // Add the last part after the last space
  ans.push_back(s.substr(oldpos));
  return ans;
}

int main() {
  std::unordered_map<std::string, int> stencil = {
      {"children", 3}, {"cats", 7},    {"samoyeds", 2}, {"pomeranians", 3},
      {"akitas", 0},   {"vizslas", 0}, {"goldfish", 5}, {"trees", 3},
      {"cars", 2},     {"perfumes", 1}};

  std::string ingredient;
  std::fstream input("./16.txt", std::ios_base::in);

  while (std::getline(input, ingredient)) {
    auto splits = split(ingredient, " ");

    bool flag = true;
    for (int i = 2; i < splits.size(); i += 2) {
      std::string key = splits[i].substr(0, splits[i].size() - 1);
      int v = std::stoi(splits[i + 1].substr(
          0, splits[i + 1].size() - 1 * (splits.size() - 2 > i)));
      bool cat_trees = (key == "cats" || key == "trees");
      bool poms_fish = (key == "pomeranians" || key == "goldfish");

      if ((cat_trees && v > stencil[key]) || (poms_fish && v < stencil[key]) ||
          (!cat_trees && !poms_fish && v == stencil[key])) {
        flag = true;
      } else {
        flag = false;
        break;
      }
    }
    if (flag) {
      int number = std::stoi(splits[1].substr(0, splits[1].size() - 1));
      std::cout << number << std::endl;
    }
  }
  return 0;
}

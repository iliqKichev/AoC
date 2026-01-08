/*
 * The problem is a classical TSP
 * The main hurdle in this case is the parsing of the input, which is difficult
 * to do in C++
 * */

#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>

std::vector<std::string> split(std::string s, std::string sep) {
  int pos = s.find(sep, pos), oldpos = 0;
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

std::tuple<std::string, std::string, int>
get_edge(std::vector<std::string> &sentence) {
  std::string name_1 = sentence[0];
  std::string name_2 = sentence.back();
  int value =
      sentence[2] == "lose" ? -std::stoi(sentence[3]) : std::stoi(sentence[3]);
  return std::make_tuple(name_1, name_2, value);
}

int route_cost(
    std::unordered_map<std::string, std::unordered_map<std::string, int>>
        &likeness,
    std::vector<std::string> route) {
  int cost = likeness[route[0]][route.back()];
  for (int i = 1; i < route.size(); i++) {
    cost += likeness[route[i - 1]][route[i]];
  }
  return cost;
}

int tsp(std::unordered_map<std::string, std::unordered_map<std::string, int>>
            &likeness) {

  std::vector<std::string> route = {};
  for (auto &[key, m] : likeness) {
    route.push_back(key);
  }
  std::sort(route.begin(), route.end());

  std::vector<std::string> best_route(route.size());
  int best_cost = -1;
  while (std::next_permutation(route.begin(), route.end())) {
    int cost = route_cost(likeness, route);
    if (best_cost < cost) {
      best_cost = cost;
      best_route = route;
    }
  }

  return best_cost;
}

void add_person(
    std::unordered_map<std::string, std::unordered_map<std::string, int>>
        &likeness,
    std::string &name) {
  likeness[name] = {};
  for (auto &[n, m] : likeness) {
    if (n == name)
      continue;
    m[name] = 0;
    likeness[name][n] = 0;
  }
}

int main() {
  std::unordered_map<std::string, std::unordered_map<std::string, int>>
      likeness;

  std::string preference;
  std::fstream input("./13.txt", std::ios_base::in);
  while (std::getline(input, preference)) {
    auto splits = split(preference.substr(0, preference.size() - 1), " ");
    auto [n1, n2, val] = get_edge(splits);
    if (likeness.find(n1) == likeness.end()) {
      add_person(likeness, n1);
    }

    if (likeness.find(n2) == likeness.end()) {
      add_person(likeness, n2);
    }
    likeness[n1][n2] += val;
    likeness[n2][n1] += val;
  }

  int best_cost = tsp(likeness);

  std::string ME = "ME";
  add_person(likeness, ME);
  int new_best_cost = tsp(likeness);
  std::cout << std::format("{} {} {}\n", best_cost, new_best_cost,
                           new_best_cost - best_cost);
}

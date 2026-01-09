#include <format>
#include <fstream>
#include <iostream>
#include <string>
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

long long calculate_cost(std::vector<int> &ammount,
                         std::vector<std::vector<int>> &coef) {
  long long cost = 1;
  for (int c = 0; c < 4; c ++) {
    long long cur_cost = 0;
    for (int i = 0; i < ammount.size(); i++) {
      // std::cout << std::format("{} {}\n", ammount[i], coef[c][i]); 
      cur_cost += ammount[i] * coef[c][i];
    }
    // std::cout << std::format("cost {} {}]\n",c, cur_cost);
    cost *= std::max(0ll, cur_cost);
    if(!cost) return cost;
  }
  return cost;
}

int main() {
  std::vector<std::vector<int>> coef(5);
  std::string ingredient;
  std::fstream input("./15.txt", std::ios_base::in);
  while (std::getline(input, ingredient)) {
    auto splits = split(ingredient, " ");
    // remove the commas
    coef.push_back(std::vector<int>(4, 0));
    coef[0].push_back(std::stoi(splits[2].substr(0, splits[2].size() - 1)));
    coef[1].push_back(std::stoi(splits[4].substr(0, splits[4].size() - 1)));
    coef[2].push_back(std::stoi(splits[6].substr(0, splits[6].size() - 1)));
    coef[3].push_back(std::stoi(splits[8].substr(0, splits[8].size() - 1)));
    coef[4].push_back(std::stoi(splits[10].substr(0, splits[8].size() - 1)));
    std::cout << std::format("{}, {}, {}, {}\n", coef[0].back(), coef[1].back(),
                             coef[2].back(), coef[3].back());
  }

  int total_amount = 100;
  long long best_cost = -1;
  std::vector<int> amount(coef[0].size(), 0);
  for (amount[0] = 0; amount[0] <= total_amount; amount[0]++) {
    for (amount[1] = 0; amount[1] <= total_amount - amount[0]; amount[1]++) {
      for (amount[2] = 1; amount[2] <= total_amount - amount[0] - amount[1]; amount[2]++) {
         amount[3] = 100 - amount[0] - amount[1] - amount[2];
        
        auto cost =calculate_cost(amount, coef);
        if(cost > best_cost){
          int cals = 0;
          for(int i =0; i < 4; i ++){
            cals += amount[i]*coef[4][i];
          }
          if(cals == 500)best_cost = cost;
        }
      }
    }
  }
  std::cout << best_cost << std::endl;
  return 0;
}

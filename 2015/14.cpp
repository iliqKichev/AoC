#include <format>
#include <fstream>
#include <iostream>
#include <string>
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

int calc_distance(int speed, int duration, int rest, int time) {
  int cycle = duration + rest;
  int distance = time / cycle * duration;
  //  std::cout << std::format("{}\t{}\t{}\n", cycle, distance, time%cycle);
  if (time % cycle < duration) {
    distance += time % cycle;
  } else {
    distance += duration;
  }
  // std::cout << distance << std::endl;
  return distance * speed;
}

int main() {
  std::vector<std::string> name;
  std::vector<int> speed, duration, rest;
  std::string preference;
  std::fstream input("./14.txt", std::ios_base::in);
  while (std::getline(input, preference)) {
    auto splits = split(preference.substr(0, preference.size() - 1), " ");
    name.push_back(splits[0]);
    speed.push_back(std::stoi(splits[3]));
    duration.push_back(std::stoi(splits[6]));
    rest.push_back(std::stoi(splits[13]));
  }

  const int TOTAL_TIME = 2503;
  int best_distance = -1;
  for (int i = 0; i < name.size(); i++) {
    int curr_dist = calc_distance(speed[i], duration[i], rest[i], TOTAL_TIME);
    std::cout << std::format("{}\t{}\n", name[i], curr_dist);
    best_distance = std::max(best_distance, curr_dist);
  }
  std::cout << best_distance << std::endl;
  
  std::vector<int> scores(name.size(), 0);
  for(int time = 1; time <= 1000; time++){
    int best = 0, best_dist = -1;
    for(int i = 0; i < name.size(); i ++){
      int curr_dist = calc_distance(speed[i], duration[i], rest[i], time);
      if(curr_dist > best_dist){
        best_dist = curr_dist;
        best = i;
      }
    }
    scores[best]++;
  }
  std::cout << "New Scores\n";
  for(int i=0; i < name.size(); i ++){
    std::cout << std::format("{}\t{}\n", name[i], scores[i]);
  }
  return 0;
}

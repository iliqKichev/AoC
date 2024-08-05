#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

bool is_nice(std::string str) {
  std::string vowels = "aeiou";
  std::vector<std::string> bad{"ab", "cd", "pq", "xy"};
  bool hasDouble = false;
  int numVowels = 0;
  for (std::size_t i = 0; i < str.size(); i++) {
    if (i < str.size() - 1) {
      if (str[i] == str[i + 1])
        hasDouble = true;

      std::string tmp = str.substr(i, 2);
      for (auto b : bad) {
        if (b == tmp)
          return false;
      }
    }
    for (auto v : vowels) {
      if (v == str[i]) {
        numVowels++;
        break;
      }
    }
  }
  return hasDouble && (numVowels >= 3);
}

bool is_nice_new(std::string str) {
  bool has_repeat = false;
  bool has_pair = false;
  for (std::size_t i = 0; i < str.size(); i++) {
    if (i < str.size() - 2) {
      if (str[i] == str[i + 2]) {
        has_repeat = true;
      }
    }
    std::string cur = str.substr(i, 2), tmp;
    for (int j = i + 2; j < str.size(); j++) {
      tmp = str.substr(j, 2);
//      std::cout << cur  << " " << tmp << std::endl;
      if (tmp == cur) {
        has_pair = true;
        break;
      }
    }
  }
//  std::cout << has_repeat << has_pair << std::endl;
  return has_repeat && has_pair;
}

int main() {
  std::string input;
  int nice = 0, nice_new = 0;
  while (std::cin >> input) {
    nice += is_nice(input);
    nice_new += is_nice_new(input);
  }
  std::cout << nice << std::endl;
  std::cout << nice_new << std::endl;
  return 0;
}

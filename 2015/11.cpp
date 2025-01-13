#include <ios>
#include <iostream>
#include <string>
#include <unordered_set>

bool is_valid(const std::string &s) {
  // Contains i, l, o
  for (const auto &c : s) {
    if (c == 'i' || c == 'l' || c == 'o')
      return false;
  }

  // Contains two pairs
  std::unordered_set<char> letters = {};
  for (std::size_t i = 0; i < s.size() - 1; i++) {
    if (s[i] == s[i + 1]) {
      letters.insert(s[i]);
      i++;
    }
  }
  if (letters.size() < 2)
    return false;

  // Consecutive letters
  bool flag = true;
  for (std::size_t i = 0; i < s.size() - 2; i++) {
    flag = true;
    for (std::size_t j = 1; j < 3; j++) {
      if (s[i + j - 1] + 1 != s[i + j]) {
        flag = false;
        break;
      }
    }
    if (flag)
      break;
  }

  return flag;
}

std::string get_next(const std::string &s) {
  auto ans = s;
  ans.back() += 1;
  std::size_t i = ans.size() - 1;
  while (i > 0 && ans[i] > 'z') {
    ans[i] = 'a';
    ans[i - 1]++;
    i--;
  }
  ans[0] = 'a' + (ans[0] - 'a') % 26;
  return ans;
}

int main() {
  std::string passwd;
  std::cin >> passwd;

  passwd = get_next(passwd);
  while (!is_valid(passwd)) {
    passwd = get_next(passwd);
  }
  std::cout << passwd << std::endl;
  return 0;
}

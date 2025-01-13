#include <iostream>
#include <sstream>
#include <string>

std::string look_and_say(const std::string &seq) {
  std::stringstream out;
  for (int i = 0; i < seq.size(); i++) {
    char cur = seq[i];
    int cur_id = i;

    while (seq[i] == cur) {
      i++;
    }
    out << i - cur_id << cur;
    i--;
  }
  return out.str();
}

int main() {
  std::string seq;
  seq.reserve(1<<15);
  std::cin >> seq;

  for (int i = 0; i < 50; i++) {
//    std::cout << std::format("{} on iteration {}\n", seq, i);
    seq = look_and_say(seq);
  }

  std::cout << seq.size() << std::endl;
  return 0;
}

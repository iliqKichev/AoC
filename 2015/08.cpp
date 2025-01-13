#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

char hex2char(const std::string &s) {
  std::string format = "0123456789ABCDEF";
  char res = 0;
  for (const auto &c : s) {
    auto pos = format.find(std::toupper(c));
    if (pos != std::string::npos) {
      res <<= 4;
      res += format.find(std::toupper(c));
    } else {
      throw std::invalid_argument(
          std::format("{} in {} is not a valid hex character", c, s));
    }
  }
  return res;
}

std::string parse_cmd(const std::string &cmd) {
  std::stringstream sstream;
  for (int i = 1; i < cmd.size() - 1; i++) {
    if (cmd[i] == '\\') {
      if (cmd[i + 1] == '"' || cmd[i + 1] == '\\') {
        sstream << cmd[i + 1];
        i++;
      } else {
        sstream << hex2char(cmd.substr(i + 2, 2));
        i += 3;
      }
    } else {
      sstream << cmd[i];
    }
  }
  return sstream.str();
}

std::string reverse_parse_cmd(const std::string& cmd){
  std::stringstream sstream;
  sstream << '"';
  for(const auto& c: cmd){
    if(c == '\\' || c == '"'){
      sstream << '\\';
    }
    sstream << c;
  }
  sstream << '"';
  return sstream.str();
}

int main() {
  std::string s, s_new, s_reverse_parse;
  s.reserve(256);
  s_new.reserve(256);
  s_reverse_parse.reserve(256);
  std::fstream file("08.txt", std::ios_base::in);

  int ans = 0;
  int ans_rp = 0;
  while (std::getline(file, s)) {
    if (s.empty()) {
      continue;
    }
    s_new = parse_cmd(s);
    s_reverse_parse = reverse_parse_cmd(s);
    ans += s.size() - s_new.size();
    ans_rp += s_reverse_parse.size() - s.size();
#ifdef DEBUG
    std::cout << std::format("{} {} {}\n", s, s_new, s_reverse_parse);
#endif
  }
  std::cout << ans << std::endl;
  std::cout << ans_rp << std::endl;
  return 0;
}

/**
 * Scratch to write what I think about the problem. In the end, they ask about
 * the signal comming from a specific wire (say wire END). Hence, a recursive
 * approach with memoization in which the Gates (still I haven't decided on
 * whether there is a need for a specific Gate class) are identified by their
 * unique output.
 *
 * Wait! One Gate can have multiple outputs - only the inputs are between 0
 * and 2. NO! The Gate can output to only one wire that can be in turn input to
 * multiple gates.
 */
#include <cstdint>
#include <fstream>
#include <iostream>
#include <queue>
#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

#define DEBUG

std::pair<bool, std::uint16_t>
get_number(const std::string &cmd,
           const std::unordered_map<std::string, std::uint16_t> &wire) {
  uint16_t in = 0;
  bool flag = false;
  try {
    in = std::stoi(cmd);
    flag = true;
  } catch (std::invalid_argument) {
    if (wire.find(cmd) != wire.end()) {
      in = wire.at(cmd);
      flag = true;
    }
  }
  return std::make_pair(flag, in);
}

bool execute_cmd(std::string cmd,
                 std::unordered_map<std::string, std::uint16_t> &wire) {
  // 123 -> x
  std::string cmd_src("^([a-z]+|[0-9]+) -> ([a-z]+)");
  // x AND y -> z
  std::string cmd_add("^([a-z]+|[0-9]+) AND ([a-z]+|[0-9]+) -> ([a-z]+)");
  // x OR y -> z
  std::string cmd_or("^([a-z]+|[0-9]+) OR ([a-z]+|[0-9]+) -> ([a-z]+)");
  // x LSHIFT 2 -> z
  std::string cmd_lsh("^([a-z]+|[0-9]+) LSHIFT ([a-z]+|[0-9]+) -> ([a-z]+)");
  // x LSHIFT 2 -> z
  std::string cmd_rsh("^([a-z]+|[0-9]+) RSHIFT ([a-z]+|[0-9]+) -> ([a-z]+)");
  // NOT y -> z
  std::string cmd_not("^NOT ([a-z]+|[0-9]+) -> ([a-z]+)");

  std::smatch m;
  if (std::regex_search(cmd, m, std::regex(cmd_src))) {
#ifdef DEBUG
    std::cout << "Command SRC\n";
#endif
    auto [flag, num] = get_number(m[1], wire);
    if (flag) {
      wire[m[2]] = num;
#ifdef DEBUG
      std::cout << "Command executed\n";
#endif
    }
    return flag;
  }

  else if (std::regex_search(cmd, m, std::regex(cmd_add))) {
#ifdef DEBUG
    std::cout << "Command AND\n";
#endif
    auto [flag1, in1] = get_number(m[1], wire);
    auto [flag2, in2] = get_number(m[2], wire);
    if (flag1 && flag2) {
      wire[m[3]] = in1 & in2;
#ifdef DEBUG
      std::cout << "Command executed\n";
#endif
    }
    return flag1 && flag2;
  }

  else if (std::regex_search(cmd, m, std::regex(cmd_or))) {
#ifdef DEBUG
    std::cout << "Command OR\n";
#endif
    auto [flag1, in1] = get_number(m[1], wire);
    auto [flag2, in2] = get_number(m[2], wire);
    if (flag1 && flag2) {
      wire[m[3]] = in1 | in2;
#ifdef DEBUG
      std::cout << "Command executed\n";
#endif
    }
    return flag1 && flag2;
  }

  else if (std::regex_search(cmd, m, std::regex(cmd_lsh))) {
#ifdef DEBUG
    std::cout << "Command LSHIFT\n";
#endif
    auto [flag1, in1] = get_number(m[1], wire);
    auto [flag2, in2] = get_number(m[2], wire);
    if (flag1 && flag2) {
      wire[m[3]] = in1 << in2;
#ifdef DEBUG
      std::cout << "Command executed\n";
#endif
    }
    return flag1 && flag2;
  }

  else if (std::regex_search(cmd, m, std::regex(cmd_rsh))) {
#ifdef DEBUG
    std::cout << "Command RSHIFT\n";
#endif
    auto [flag1, in1] = get_number(m[1], wire);
    auto [flag2, in2] = get_number(m[2], wire);
    if (flag1 && flag2) {
      wire[m[3]] = in1 >> in2;
#ifdef DEBUG
      std::cout << "Command executed\n";
#endif
    }
    return flag1 && flag2;
  }

  else if (std::regex_search(cmd, m, std::regex(cmd_not))) {
#ifdef DEBUG
    std::cout << "Command NOT\n";
#endif
    auto [flag, num] = get_number(m[1], wire);
    if (flag) {
      wire[m[2]] = ~num;
#ifdef DEBUG
      std::cout << "Command executed\n";
#endif
    }
    return flag;
  }

  return false;
}

int main() {
  std::unordered_map<std::string, std::uint16_t> wire;
  std::queue<std::string> commands;

  std::fstream file("07_2.txt", std::ios_base::in);

  std::string cmd;
  while (std::getline(file, cmd)) {
    commands.push(cmd);
  }

  while (!commands.empty()) {
#ifdef DEBUG
    std::cout << std::format("{} elements in queue\t top command: {}\n",
                             commands.size(), commands.front());
#endif
    std::string c = commands.front();
    commands.pop();

    if (c.empty()) {
      continue;
    }

    if (!execute_cmd(c, wire)) {
      commands.push(c);
    }
  }

  for (auto &i : wire) {
    std::cout << i.first << " " << i.second << std::endl;
  }

  return 0;
}

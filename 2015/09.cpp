#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>

const size_t MAX_VERTEX = 128;

std::size_t shortest_path(std::size_t i, std::size_t j, std::size_t k,
                   std::vector<std::vector<std::size_t>> &node) {
  if(k == 0){
    return node[i][j]; 
  }

  auto a = shortest_path(i, j, k-1, node);
  auto b = shortest_path(i, k, k-1, node);
  auto c = shortest_path(k, j, k-1, node);

  return std::min(a, b+c);
}

int main() {
  std::unordered_map<std::string, std::size_t> vertex;
  std::vector<std::vector<std::size_t>> node(
      MAX_VERTEX, std::vector<size_t>(MAX_VERTEX, 10000));

  std::fstream file("09.txt", std::ios_base::in);

  std::string line;
  std::regex line_parser("^([A-z]+) to ([A-z]+) = ([0-9]+)");
  while (std::getline(file, line)) {
    if (line.empty()) {
      continue;
    }

    std::smatch m;
    std::regex_match(line, m, line_parser);
    if (vertex[m[1]] == 0) {
      vertex[m[1]] = vertex.size();
    }
    if (vertex[m[2]] == 0) {
      vertex[m[2]] = vertex.size();
    }
    node[vertex[m[1]]][vertex[m[2]]] = std::stoi(m[3]);
    node[vertex[m[2]]][vertex[m[1]]] = std::stoi(m[3]);
  }

  shortest_path(1, vertex.size(), vertex.size(), node);

  // Printing
  for (const auto &[k, v] : vertex) {
    std::cout << std::format("{} is {}\n", k, v);
  }
  
  std::size_t min_val = 10000;
  std::cout << "      ";
  for (std::size_t j = 1; j <= vertex.size(); j++) {
    std::cout << std::setw(5) << j << " ";
  }
  std::cout << std::endl;
  for (std::size_t i = 1; i <= vertex.size(); i++) {
    std::cout << std::setw(5) << i << " ";
    for (std::size_t j = 1; j <= vertex.size(); j++) {
      std::cout << std::setw(5) << node[i][j] << " ";
      min_val = std::min(min_val, node[i][j]);
    }
    std::cout << std::endl;
  }
    std::cout << min_val << std::endl;
  return 0;
}

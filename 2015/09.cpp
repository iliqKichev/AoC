#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <regex>
#include <string>
#include <unordered_map>

const size_t MAX_VERTEX = 128;
#ifdef MIN_PATH
const size_t INF = 10000;
#else 
const size_t INF = 0;
#endif

// Floyd-Warschal - not the right algorithm
std::size_t floyd_warschal(std::size_t i, std::size_t j, std::size_t k,
                           std::vector<std::vector<std::size_t>> &node) {
  if (k == 0) {
    return node[i][j];
  }

  auto a = floyd_warschal(i, j, k - 1, node);
  auto b = floyd_warschal(i, k, k - 1, node);
  auto c = floyd_warschal(k, j, k - 1, node);

  return std::min(a, b + c);
}

void print_vertecies(
    const std::unordered_map<std::string, std::size_t> &vertex) {
  for (const auto &[k, v] : vertex) {
    std::cout << std::format("{} is {}\n", k, v);
  }
}

void print_nodes(const std::vector<std::vector<std::size_t>> &node,
                 std::size_t num_vertecies) {
  std::cout << "      ";
  for (std::size_t j = 1; j <= num_vertecies; j++) {
    std::cout << std::setw(5) << j << " ";
  }
  std::cout << std::endl;
  for (std::size_t i = 1; i <= num_vertecies; i++) {
    std::cout << std::setw(5) << i << " ";
    for (std::size_t j = 1; j <= num_vertecies; j++) {
      std::cout << std::setw(5) << node[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

std::size_t check_path(const std::vector<std::vector<std::size_t>> &node,
                       const std::vector<std::size_t> &perm) {
  std::size_t res = 0;
  for (int i = 1; i < perm.size(); i++) {
    res += node[perm[i - 1]][perm[i]];
  }
  return res;
}

std::size_t optimal_path(const std::vector<std::vector<std::size_t>> &node,
                          std::size_t num_vertecies) {

  // Fill indecies
  std::vector<std::size_t> perm(num_vertecies);
  std::iota(perm.begin(), perm.end(), 1);

  auto path = check_path(node, perm);
  while (std::next_permutation(perm.begin(), perm.end())) {
    #ifdef MIN_PATH
    min_path = std::min(path, check_path(node, perm));
#else
    path = std::max(path, check_path(node, perm));
#endif
  }
  return path;
}

int main() {
  std::unordered_map<std::string, std::size_t> vertex;
  std::vector<std::vector<std::size_t>> node(
      MAX_VERTEX, std::vector<size_t>(MAX_VERTEX, INF));

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

  // floyd_warschal(1, vertex.size(), vertex.size(), node);
  print_vertecies(vertex);
  print_nodes(node, vertex.size());

  std::cout << optimal_path(node, vertex.size()) << std::endl;

  return 0;
}

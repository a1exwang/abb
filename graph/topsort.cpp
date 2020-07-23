#include <cassert>
#include <cctype>

#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<size_t> topology_sort(
    const std::unordered_set<size_t> &vertexes,
    const std::unordered_map<size_t, std::vector<size_t>> &adj_tables) {

  std::unordered_map<size_t, size_t> in_degrees;
  for (auto &[_, adjs] : adj_tables) {
    for (auto adj : adjs) {
      in_degrees[adj]++;
    }
  }

  std::unordered_set<size_t> start_nodes;
  for (auto vertex : vertexes) {
    if (in_degrees[vertex] == 0) {
      start_nodes.insert(vertex);
    }
  }

  std::vector<size_t> result;
  result.reserve(vertexes.size());

  while (!start_nodes.empty()) {
    std::unordered_set<size_t> new_start_nodes;
    for (auto start_node : start_nodes) {
      result.push_back(start_node);
      if (adj_tables.find(start_node) != adj_tables.end()) {
        for (auto adj : adj_tables.at(start_node)) {
          in_degrees[adj]--;
          assert(in_degrees[adj] >= 0);
          if (in_degrees[adj] == 0) {
            new_start_nodes.insert(adj);
          }
        }
      }
    }
    start_nodes = std::move(new_start_nodes);
  }

  if (result.size() < vertexes.size()) {
    throw std::invalid_argument("loop found in DAG");
  } else {
    return result;
  }
}


int main() {
  size_t nodes[] = {1, 2, 3, 4, 5};
  size_t edges[][2] = {{1,2}, {2,3}, {1, 3}, {2,4}};

  std::unordered_set<size_t> vertexes;
  for (auto node : nodes) {
    vertexes.insert(node);
  }

  std::unordered_map<size_t, std::vector<size_t>> adj_tables(vertexes.size());
  for (auto [from, to] : edges) {
    adj_tables[from].push_back(to);
  }

  auto sorted = topology_sort(vertexes, adj_tables);
  for (auto item : sorted) {
    std::cout << item << std::endl;
  }
}
#include <iostream>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>


struct Compare {
  explicit Compare(const std::unordered_map<size_t, int64_t> &distances)
      :distances(distances) {}

  bool operator()(size_t lhs, size_t rhs) const {
    return distances.at(lhs) > distances.at(rhs);
  }
  const std::unordered_map<size_t, int64_t> &distances;
};

std::unordered_map<size_t, int64_t> dijkstra(
    const std::unordered_set<size_t> &vertexes,
    const std::unordered_map<size_t, std::vector<std::tuple<size_t, int64_t>>> &adj_tables,
    size_t start_node_id) {

  constexpr int64_t InfDistance = std::numeric_limits<int64_t>::max();

  // Initialize all distances to INF
  std::unordered_map<size_t, int64_t> distances;
  for (auto node_id : vertexes) {
    // use max as inf
    distances[node_id] = InfDistance;
  }
  distances[start_node_id] = 0;

  Compare compare(distances);
  // node_id, distance
  std::priority_queue<size_t, std::vector<size_t>, Compare> pq(compare);

  // assume all distances >= 0
  pq.push(start_node_id);

  std::unordered_set<size_t> visited;
  while (!pq.empty() && distances[pq.top()] != InfDistance) {
    auto current_node = pq.top();
    pq.pop();
    visited.insert(current_node);
    if (adj_tables.find(current_node) != adj_tables.end()) {
      for (auto [adj, adj_distance] : adj_tables.at(current_node)) {
        if (visited.find(adj) == visited.end()) {
          auto cur_min = distances[adj];
          if (distances[current_node] + adj_distance < distances[adj]) {
            distances[adj] = distances[current_node] + adj_distance;
          }
          pq.push(adj);
        }
      }
    }
  }
  return distances;
}

int main() {
  std::unordered_set<size_t> vertexes = {0,1,2,3,4};
  std::unordered_map<size_t, std::vector<std::tuple<size_t, int64_t>>> adj_tables = {
      {0, {{1,1}, {2,3}, {4,2}}},
      {1, {{0,2}, {2,1}, {3,5}}},
      {2, {{0,2}}},
      {3, {{4,1}}},
  };

  auto distances = dijkstra(vertexes, adj_tables, 0);
  for (auto [node_id, distance] : distances) {
    std::cout << node_id << ": " << distance << std::endl;
  }

}
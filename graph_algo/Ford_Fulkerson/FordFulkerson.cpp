#include <iostream>
#include <vector>
#include <limits>

struct Edge {
  Edge() = default;

  Edge(int f, int t, int c) : from(f), to(t), capacity(c), flow(0) {
  }

  int from;
  int to;
  int capacity;
  int flow;
};

void AddEdge(std::vector<std::vector<int>>& graph, std::vector<Edge>& edges, int from, int to, int capacity) {
  size_t i = edges.size();
  edges.emplace_back(from, to, capacity);
  edges.emplace_back(to, from, 0);
  graph[from].push_back(static_cast<int>(i));
  graph[to].push_back(static_cast<int>(i + 1));
}

bool Dfs(const std::vector<std::vector<int>>& graph, std::vector<Edge>& edges, std::vector<bool>& visited, int u, int t,
         int min_cap) {
  if (u == t) {
    return true;
  }
  visited[u] = true;
  for (const auto& idx : graph[u]) {
    Edge& edge = edges[idx];
    int v = edge.to;
    if (!visited[v] && edge.capacity - edge.flow >= min_cap && Dfs(graph, edges, visited, v, t, min_cap)) {
      edge.flow += min_cap;
      edges[idx ^ 1].flow -= min_cap;
      return true;
    }
  }
  return false;
}

int64_t FordFulkerson(std::vector<std::vector<int>>& graph, std::vector<Edge>& edges, int s, int t) {
  int64_t max_flow = 0;
  size_t v = graph.size();
  for (int curr_flow = 1e9; curr_flow > 0; curr_flow /= 2) {
    std::vector<bool> visited(v, false);
    while (Dfs(graph, edges, visited, s, t, curr_flow)) {
      max_flow += curr_flow;
      visited.assign(v, false);
    }
  }
  return max_flow;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int>> graph(n);
  std::vector<Edge> edges;
  for (int i = 0; i < m; ++i) {
    int from = 0;
    int to = 0;
    int capacity = 0;
    std::cin >> from >> to >> capacity;
    AddEdge(graph, edges, from - 1, to - 1, capacity);
  }
  std::cout << FordFulkerson(graph, edges, 0, n - 1) << "\n";
}

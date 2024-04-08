#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>

struct Edge {
  Edge() = default;
  Edge(int64_t s, int64_t f, int64_t cap, int64_t fl) : from(s), to(f), capacity(cap), flow(fl) {
  }
  int64_t from;
  int64_t to;
  int64_t capacity;
  int64_t flow;
};

int64_t Karp(std::vector<std::vector<int64_t>>& graph, std::vector<Edge>& edges, int64_t s, int64_t t) {
  size_t n = graph.size();
  for (auto& edge : edges) {
    edge.flow = 0;
  }
  int64_t max_flow = 0;
  while (true) {
    std::vector<int64_t> parent(n, -1);
    std::vector<int64_t> min_capacity(n, 1e9);
    std::queue<int64_t> q;
    q.push(s);
    parent[s] = -2;
    min_capacity[s] = 1e9;
    while (!q.empty()) {
      int64_t u = q.front();
      q.pop();
      for (const auto& v : graph[u]) {
        Edge& edge = edges[v];
        if (parent[edge.to] == -1 && edge.capacity > edge.flow) {
          parent[edge.to] = v;
          min_capacity[edge.to] = std::min(min_capacity[u], edge.capacity - edge.flow);
          if (edge.to == t) {
            break;
          }
          q.push(edge.to);
        }
      }
    }
    if (parent[t] == -1) {
      break;
    }
    max_flow += min_capacity[t];
    int64_t u = t;
    while (u != s) {
      int64_t v = parent[u];
      edges[v].flow += min_capacity[t];
      edges[v ^ 1].flow -= min_capacity[t];
      u = edges[v].from;
    }
  }
  return max_flow;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int64_t>> graph(n);
  std::vector<Edge> edges;
  for (int i = 0; i < m; ++i) {
    int64_t from = 0;
    int64_t to = 0;
    int64_t capacity = 0;
    std::cin >> from >> to >> capacity;
    graph[from - 1].push_back(static_cast<int64_t>(edges.size()));
    edges.emplace_back(from - 1, to - 1, capacity, 0);
    graph[to - 1].push_back(static_cast<int64_t>(edges.size()));
    edges.emplace_back(to - 1, from - 1, 0, 0);
  }
  std::cout << Karp(graph, edges, 0, n - 1) << "\n";
}

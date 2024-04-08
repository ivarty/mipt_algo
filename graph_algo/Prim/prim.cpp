#include <climits>
#include <iostream>
#include <vector>
#include <queue>

using Graph = std::vector<std::vector<std::pair<int, int>>>;

int Prim(const Graph& graph, int n) {
  std::vector<bool> visited(n, false);
  std::vector<int> dist(n, INT_MAX);
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
  pq.emplace(0, 0);
  dist[0] = 0;
  int min_weight = 0;
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    visited[u] = true;
    for (const auto& edge : graph[u]) {
      int v = edge.first;
      int weight = edge.second;
      if (!visited[v] && weight < dist[v]) {
        dist[v] = weight;
        pq.emplace(weight, v);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    min_weight += dist[i];
  }
  return min_weight;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int b = 0;
    int e = 0;
    int w = 0;
    std::cin >> b >> e >> w;
    graph[b - 1].emplace_back(e - 1, w);
    graph[e - 1].emplace_back(b - 1, w);
  }
  std::cout << Prim(graph, n) << "\n";
}

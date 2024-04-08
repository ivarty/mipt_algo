#include <iostream>
#include <vector>
#include <queue>

void Dijkstra(std::vector<std::vector<std::pair<int, int>>>& graph, int start, std::vector<int>& dist) {
  size_t n = graph.size();
  dist.resize(n, 2009000999);
  dist[start] = 0;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
  pq.emplace(0, start);
  while (!pq.empty()) {
    int curr_vertex = pq.top().second;
    int curr_dist = pq.top().first;
    pq.pop();
    if (curr_dist > dist[curr_vertex]) {
      continue;
    }
    for (const auto& neighbor : graph[curr_vertex]) {
      int next_vertex = neighbor.first;
      int weight = neighbor.second;

      int new_dist = curr_dist + weight;
      if (new_dist < dist[next_vertex]) {
        dist[next_vertex] = new_dist;
        pq.emplace(new_dist, next_vertex);
      }
    }
  }
  for (const auto& a : dist) {
    std::cout << a << " ";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  int k = 0;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> graph(n);
    for (int j = 0; j < m; ++j) {
      int start = 0;
      int end = 0;
      int weight = 0;
      std::cin >> start >> end >> weight;
      graph[start].emplace_back(end, weight);
      graph[end].emplace_back(start, weight);
    }
    int start = 0;
    std::cin >> start;
    std::vector<int> dist;
    Dijkstra(graph, start, dist);
    std::cout << "\n";
  }
}

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

class Edge {
 public:
  Edge(int to, int64_t capacity, int rev) : to(to), capacity(capacity), flow(0), rev(rev) {
  }

 public:
  int to;
  int64_t capacity;
  int64_t flow;
  int rev;
};

void AddEdge(std::vector<std::vector<Edge>>& graph, int from, int to, int64_t capacity) {
  Edge a(to, capacity, static_cast<int>(graph[to].size()));
  graph[from].emplace_back(a);
  Edge b(from, 0, static_cast<int>(graph[from].size() - 1));
  graph[to].emplace_back(b);
}

bool Bfs(std::vector<std::vector<Edge>>& graph, std::vector<int>& level, int source, int sink) {
  std::fill(level.begin(), level.end(), -1);
  level[source] = 0;
  std::queue<int> q;
  q.push(source);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (const Edge& e : graph[u]) {
      if (level[e.to] < 0 && e.flow < e.capacity) {
        level[e.to] = level[u] + 1;
        q.push(e.to);
      }
    }
  }
  return level[sink] >= 0;
}

int64_t Dfs(std::vector<std::vector<Edge>>& graph, std::vector<int>& level, std::vector<int>& ptr, int u, int t,
            int64_t min_capacity) {
  if (u == t) {
    return min_capacity;
  }
  for (int& i = ptr[u]; i < static_cast<int>(graph[u].size()); ++i) {
    Edge& e = graph[u][i];
    if (level[e.to] == level[u] + 1 && e.flow < e.capacity) {
      int64_t cap = Dfs(graph, level, ptr, e.to, t, std::min(min_capacity, e.capacity - e.flow));
      if (cap > 0) {
        e.flow += cap;
        graph[e.to][e.rev].flow -= cap;
        return cap;
      }
    }
  }
  return 0;
}

int64_t Dinic(std::vector<std::vector<Edge>>& graph, int s, int t) {
  int64_t max_flow = 0;
  std::vector<int> level(graph.size());
  std::vector<int> ptr(graph.size());
  while (Bfs(graph, level, s, t)) {
    std::fill(ptr.begin(), ptr.end(), 0);
    while (int64_t cap = Dfs(graph, level, ptr, s, t, 1e10)) {
      max_flow += cap;
    }
  }
  return max_flow;
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<std::vector<Edge>> graph(n + 1);
  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    int64_t capacity = 0;
    std::cin >> u >> v >> capacity;
    AddEdge(graph, u, v, capacity);
  }
  int64_t max_flow = Dinic(graph, 1, n);
  std::cout << max_flow << "\n";
}

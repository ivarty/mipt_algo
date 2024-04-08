#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class Graph {
 public:
  Graph() = default;

  explicit Graph(int size) {
    graph_.resize(size);
    parent_.resize(size, -1);
    dist_.resize(size, -1);
  }

  void BFS() {
    std::queue<int> queue;
    queue.push(start_ - 1);
    dist_[start_ - 1] = 0;
    while (!queue.empty()) {
      int v = queue.front();
      queue.pop();
      for (size_t i = 0; i < graph_[v].size(); ++i) {
        int u = graph_[v][i];
        if (dist_[u] == -1) {
          dist_[u] = dist_[v] + 1;
          parent_[u] = v;
          queue.push(u);
        }
      }
    }
  }

  friend std::istream& operator>>(std::istream& in, Graph& graph) {
    int n = 0;
    int m = 0;
    in >> n >> m;
    int start = 0;
    int finish = 0;
    in >> start >> finish;
    Graph g(n);
    g.start_ = start;
    g.finish_ = finish;
    for (int i = 0; i < m; ++i) {
      int a = 0;
      int b = 0;
      in >> a >> b;
      --a;
      --b;
      g.graph_[a].push_back(b);
      g.graph_[b].push_back(a);
    }
    graph = g;
    return in;
  }

  int& Dist() {
    return dist_[finish_ - 1];
  }

  const int& Dist() const {
    return dist_[finish_ - 1];
  }

  std::vector<int> Path() {
    std::vector<int> path;
    int vertex = finish_ - 1;
    while (vertex != start_ - 1) {
      path.push_back(vertex + 1);
      vertex = parent_[vertex];
    }
    path.push_back(start_);
    std::reverse(path.begin(), path.end());
    return path;
  }

 private:
  std::vector<std::vector<int>> graph_;
  std::vector<int> dist_;
  std::vector<int> parent_;
  int start_;
  int finish_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Graph graph;
  std::cin >> graph;
  graph.BFS();
  if (graph.Dist() == -1) {
    std::cout << graph.Dist() << "\n";
    return 0;
  }
  std::cout << graph.Dist() << "\n";
  auto path = graph.Path();
  for (const auto& vertex : path) {
    std::cout << vertex << " ";
  }
  std::cout << "\n";
}

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

enum class Color { WHITE, GRAY, BLACK };

class Graph {
 public:
  Graph() = default;

  explicit Graph(int n) {
    graph_.resize(n + 1);
    colors_.resize(n + 1, Color::WHITE);
    time_in_.resize(n + 1, 0);
    time_up_.resize(n + 1, 0);
  }

  std::set<int> DFS() {
    time_ = 0;
    for (size_t i = 1; i < graph_.size(); ++i) {
      if (colors_[i] == Color::WHITE) {
        DFSvisit(i, true);
      }
    }
    return articulation_points_;
  }

  friend std::istream& operator>>(std::istream& in, Graph& graph) {
    int n = 0;
    int m = 0;
    in >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; ++i) {
      int a = 0;
      int b = 0;
      in >> a >> b;
      g.graph_[a].push_back(b);
      g.graph_[b].push_back(a);
    }
    graph = g;
    return in;
  }

 private:
  void DFSvisit(int u, bool is_root) {
    colors_[u] = Color::GRAY;
    time_up_[u] = time_;
    ++time_;
    time_in_[u] = time_;
    int n_children = 0;
    for (const auto& neighbour : graph_[u]) {
      if (colors_[neighbour] == Color::WHITE) {
        ++n_children;
        DFSvisit(neighbour, false);
        time_up_[u] = std::min(time_up_[neighbour], time_up_[u]);
        if (!is_root && time_in_[u] <= time_up_[neighbour]) {
          articulation_points_.insert(u);
        }
      }
      if (colors_[neighbour] == Color::GRAY) {
        time_up_[u] = std::min(time_up_[u], time_in_[neighbour]);
      }
    }
    if (is_root && n_children > 1) {
      articulation_points_.insert(u);
    }
    colors_[u] = Color::BLACK;
  }

 private:
  std::vector<std::vector<int>> graph_;
  std::vector<Color> colors_;
  std::vector<int> time_in_;
  std::vector<int> time_up_;
  std::set<int> articulation_points_;
  int time_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Graph graph;
  std::cin >> graph;
  auto points = graph.DFS();
  std::cout << points.size() << "\n";
  for (const auto& vertex : points) {
    std::cout << vertex << "\n";
  }
}

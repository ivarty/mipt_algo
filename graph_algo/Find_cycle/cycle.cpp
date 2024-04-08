#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

enum class Color { WHITE, GRAY, BLACK };

class Graph {
 public:
  Graph() = default;

  explicit Graph(int n) {
    graph_.resize(n + 1);
    colors_.resize(n + 1, Color::WHITE);
  }

  bool DFS() {
    for (size_t i = 1; i < graph_.size(); ++i) {
      if (colors_[i] == Color::WHITE) {
        if (DFSvisit(i)) {
          return true;
        }
      }
    }
    return false;
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
    }
    graph = g;
    return in;
  }

  std::vector<int> Cycle() {
    std::vector<int> cycle;
    size_t size = parent_.size() - 1;
    size_t i = size - 1;
    cycle.push_back(parent_[size]);
    while (parent_[size] != parent_[i]) {
      cycle.push_back(parent_[i]);
      --i;
    }
    std::reverse(cycle.begin(), cycle.end());
    return cycle;
  }

 private:
  bool DFSvisit(int u) {
    colors_[u] = Color::GRAY;
    parent_.push_back(u);
    for (const auto& neighbour : graph_[u]) {
      if (colors_[neighbour] == Color::GRAY) {
        parent_.push_back(neighbour);
        return true;
      }
      if (colors_[neighbour] == Color::WHITE) {
        if (DFSvisit(neighbour)) {
          return true;
        }
      }
    }
    colors_[u] = Color::BLACK;
    parent_.pop_back();
    return false;
  }

 private:
  std::vector<std::vector<int>> graph_;
  std::vector<Color> colors_;
  std::vector<int> parent_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Graph graph;
  std::cin >> graph;
  if (graph.DFS()) {
    std::cout << "YES\n";
    std::vector<int> cycle = graph.Cycle();
    for (const auto& vertex : cycle) {
      std::cout << vertex << " ";
    }
    std::cout << "\n";
  } else {
    std::cout << "NO\n";
  }
}

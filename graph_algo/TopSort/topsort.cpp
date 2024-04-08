#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <queue>

enum class Color { WHITE, GRAY, BLACK };

class Graph {
 public:
  Graph() = default;

  explicit Graph(int n) {
    graph_.resize(n + 1);
    colors_.resize(n + 1, Color::WHITE);
    top_sort_.reserve(n + 1);
  }

  std::vector<int> DFS() {
    for (size_t i = 1; i < graph_.size(); ++i) {
      if (colors_[i] == Color::WHITE) {
        if (DFSvisit(i)) {
          std::vector<int> none;
          return none;
        }
      }
    }
    std::reverse(top_sort_.begin(), top_sort_.end());
    return top_sort_;
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

 private:
  bool DFSvisit(int u) {
    colors_[u] = Color::GRAY;
    for (const auto& neighbour : graph_[u]) {
      if (colors_[neighbour] == Color::GRAY) {
        return true;
      }
      if (colors_[neighbour] == Color::WHITE) {
        if (DFSvisit(neighbour)) {
          return true;
        }
      }
    }
    colors_[u] = Color::BLACK;
    top_sort_.push_back(u);
    return false;
  }

 private:
  std::vector<std::vector<int>> graph_;
  std::vector<Color> colors_;
  std::vector<int> top_sort_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Graph graph;
  std::cin >> graph;
  std::vector<int> top_sort = graph.DFS();
  if (top_sort.empty()) {
    std::cout << -1 << "\n";
    return 0;
  }
  for (const auto& sort : top_sort) {
    std::cout << sort << " ";
  }
  std::cout << "\n";
}

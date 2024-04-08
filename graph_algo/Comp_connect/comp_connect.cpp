#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
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
    component_number_.resize(n + 1, 0);
    reversed_graph_.resize(n + 1);
  }

  void DFS() {
    for (size_t i = 1; i < graph_.size(); ++i) {
      if (colors_[i] == Color::WHITE) {
        DFSvisit(i);
      }
    }
    std::reverse(top_sort_.begin(), top_sort_.end());
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
      g.reversed_graph_[b].push_back(a);
    }
    graph = g;
    return in;
  }

  std::pair<int, std::vector<int>> SCC() {
    DFS();
    int col = 1;
    for (const auto& vertex : top_sort_) {
      if (component_number_[vertex] == 0) {
        DFSvisit2(vertex, col);
        ++col;
      }
    }
    --col;
    return {col, component_number_};
  }

 private:
  void DFSvisit(int u) {
    colors_[u] = Color::BLACK;
    for (const auto& neighbour : graph_[u]) {
      if (colors_[neighbour] == Color::WHITE) {
        DFSvisit(neighbour);
      }
    }
    top_sort_.push_back(u);
  }

  void DFSvisit2(int u, int col) {
    component_number_[u] = col;
    for (const auto& vertex : reversed_graph_[u]) {
      if (component_number_[vertex] == 0) {
        DFSvisit2(vertex, col);
      }
    }
  }

 private:
  std::vector<std::vector<int>> graph_;
  std::vector<std::vector<int>> reversed_graph_;
  std::vector<Color> colors_;
  std::vector<int> top_sort_;
  std::vector<int> component_number_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Graph graph;
  std::cin >> graph;
  auto scc = graph.SCC();
  std::cout << scc.first << "\n";
  for (const auto& vertex : scc.second) {
    if (vertex != 0) {
      std::cout << vertex << " ";
    }
  }
  std::cout << "\n";
}

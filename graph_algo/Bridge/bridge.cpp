#include <iostream>
#include <utility>
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
    time_in_.resize(n + 1, 1e9);
    time_up_.resize(n + 1, 1e9);
  }

  std::set<int> DFS() {
    time_ = 0;
    for (size_t i = 1; i < graph_.size(); ++i) {
      if (colors_[i] == Color::WHITE) {
        DFSvisit(static_cast<int>(i));
      }
    }
    return bridge_;
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
      g.graph_[a].emplace_back(b, i + 1);
      g.graph_[b].emplace_back(a, i + 1);
    }
    graph = g;
    return in;
  }

 private:
  void DFSvisit(int v, int par = -1) {
    colors_[v] = Color::GRAY;
    time_in_[v] = time_up_[v] = ++time_;
    for (const auto& neighbour : graph_[v]) {
      if (neighbour.second == par) {
        continue;
      }
      if (colors_[neighbour.first] == Color::GRAY) {
        time_up_[v] = std::min(time_up_[v], time_in_[neighbour.first]);
      }
      if (colors_[neighbour.first] == Color::WHITE) {
        DFSvisit(neighbour.first, neighbour.second);
        time_up_[v] = std::min(time_up_[v], time_up_[neighbour.first]);
        if (time_in_[v] < time_up_[neighbour.first]) {
          bridge_.insert(neighbour.second);
        }
      }
    }
    colors_[v] = Color::BLACK;
  }

 private:
  std::vector<std::vector<std::pair<int32_t, int32_t>>> graph_;
  std::vector<Color> colors_;
  std::vector<int> time_in_;
  std::vector<int> time_up_;
  std::set<int> bridge_;
  int time_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Graph graph;
  std::cin >> graph;
  auto bridges = graph.DFS();
  std::cout << bridges.size() << "\n";
  for (const auto& vertex : bridges) {
    std::cout << vertex << "\n";
  }
}

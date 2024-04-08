#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <queue>

enum class Color { BLACK, WHITE };

class Graph {
 public:
  Graph() = default;

  explicit Graph(int size) {
    graph_.resize(size + 1);
    dist_.resize(size + 1, 1e5);
    color_.resize(size + 1, Color::WHITE);
  }

  void BFS() {
    std::vector<std::queue<int>> queue(10 * graph_.size());
    queue[0].push(start_);
    dist_[start_] = 0;
    for (auto& q : queue) {
      while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (color_[v] == Color::WHITE) {
          color_[v] = Color::BLACK;
          for (const auto& neighbour : graph_[v]) {
            if (dist_[neighbour.first] > dist_[v] + neighbour.second) {
              queue[dist_[v] + neighbour.second].push(neighbour.first);
              dist_[neighbour.first] = dist_[v] + neighbour.second;
            }
          }
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
      int c = 0;
      in >> a >> b >> c;
      g.graph_[a].emplace_back(b, c);
    }
    graph = g;
    return in;
  }

  int& Dist() {
    return dist_[finish_];
  }

  const int& Dist() const {
    return dist_[finish_];
  }

 private:
  std::vector<std::vector<std::pair<int, int>>> graph_;
  std::vector<int> dist_;
  std::vector<Color> color_;
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
  if (graph.Dist() == 1e5) {
    std::cout << -1 << "\n";
    return 0;
  }
  std::cout << graph.Dist() << "\n";
}

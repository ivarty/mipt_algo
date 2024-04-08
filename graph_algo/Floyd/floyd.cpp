#include <algorithm>
#include <iostream>
#include <vector>

class Graph {

 public:
  Graph() = default;

  explicit Graph(int n) {
    graph_.resize(n * n + n);
    ver_ = n;
  }

  friend std::istream& operator>>(std::istream& in, Graph& graph) {
    int n = 0;
    in >> n;
    Graph g(n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        std::cin >> g.graph_[i * n + j];
      }
    }
    graph = g;
    return in;
  }

  std::vector<int> Floyd() {
    for (int k = 0; k < ver_; ++k) {
      for (int x = 0; x < ver_; ++x) {
        for (int y = 0; y < ver_; ++y) {
          graph_[x * ver_ + y] = std::min(graph_[x * ver_ + y], graph_[x * ver_ + k] + graph_[k * ver_ + y]);
        }
      }
    }
    return graph_;
  }

  int Ver() const {
    return ver_;
  }

 private:
  std::vector<int> graph_;
  int ver_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Graph graph;
  std::cin >> graph;
  auto m = graph.Floyd();
  for (int i = 0; i < graph.Ver(); ++i) {
    for (int j = 0; j < graph.Ver(); ++j) {
      std::cout << m[i * graph.Ver() + j] << " ";
    }
    std::cout << "\n";
  }
}

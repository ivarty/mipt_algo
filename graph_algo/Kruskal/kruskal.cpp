#include <cstdint>
#include <iostream>
#include <algorithm>
#include <ratio>
#include <utility>
#include <vector>

class Edge {
 public:
  Edge(int a, int b, int w) : weight(w), u(a), v(b) {
  }

 public:
  int weight;
  int u;
  int v;
};

class DSU {
 public:
  explicit DSU(int vertex) {
    parent_.resize(vertex + 1);
    rank_.resize(vertex + 1);
    for (int i = 1; i < vertex + 1; ++i) {
      MakeSet(i);
    }
  }

  int FindSet(int x) {
    while (x != parent_[x]) {
      x = parent_[x];
    }
    return x;
  }

  void Union(int x, int y) {
    x = FindSet(x);
    y = FindSet(y);
    if (rank_[x] > rank_[y]) {
      parent_[y] = x;
    } else if (rank_[x] < rank_[y]) {
      parent_[x] = y;
    } else {
      parent_[x] = y;
      ++rank_[y];
    }
  }

  void MakeSet(int x) {
    parent_[x] = x;
  }

 private:
  std::vector<int> parent_;
  std::vector<int> rank_;
};

class Graph {
 public:
  Graph() = default;

  explicit Graph(int n) {
    graph_.reserve(n + 1);
    ver_ = n;
  }

  int64_t Kruskal() {
    int64_t w = 0;
    DSU dsu(ver_);
    for (const auto& edge : graph_) {
      if (dsu.FindSet(edge.u) != dsu.FindSet(edge.v)) {
        dsu.Union(edge.u, edge.v);
        w += edge.weight;
      }
    }
    return w;
  }

  friend std::istream& operator>>(std::istream& in, Graph& graph) {
    int n = 0;
    int m = 0;
    in >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; ++i) {
      int a = 0;
      int b = 0;
      int w = 0;
      in >> a >> b >> w;
      Edge edge(a, b, w);
      g.graph_.push_back(edge);
    }
    graph = g;
    return in;
  }

 private:
  std::vector<Edge> graph_;
  int ver_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Graph graph;
  std::cin >> graph;
  std::cout << graph.Kruskal() << "\n";
}

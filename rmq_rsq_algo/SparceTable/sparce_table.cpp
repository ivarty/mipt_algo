#include <cstdint>
#include <iostream>
#include <vector>

class Edge {
 public:
  Edge() = default;

  Edge(int x, int y, int w) : first(x), second(y), weight(w) {
  }

 public:
  int32_t first;
  int32_t second;
  int32_t weight;
};

class DSU {
 public:
  explicit DSU(int32_t vertex) {
    parent_.resize(vertex);
    rank_.resize(vertex, 0);
    weight_.resize(vertex, 0);
    for (int32_t i = 0; i < vertex; ++i) {
      MakeSet(i);
    }
  }

  int32_t FindSet(int32_t x) {
    if (x == parent_[x]) {
      return x;
    }
    return parent_[x] = FindSet(parent_[x]);
  }

  void Union(int32_t x, int32_t y, int32_t w) {
    x = FindSet(x);
    y = FindSet(y);
    if (rank_[x] > rank_[y]) {
      parent_[y] = x;
      weight_[x] += w + weight_[y];
    }
    if (rank_[x] < rank_[y]) {
      parent_[x] = y;
      weight_[y] += w + weight_[x];
    }
    if (rank_[x] == rank_[y] && x != y) {
      parent_[x] = y;
      ++rank_[y];
      weight_[y] += w + weight_[x];
    }
    if (x == y) {
      weight_[x] += w;
    }
  }

  void MakeSet(int32_t x) {
    parent_[x] = x;
  }

  int64_t Weight(int32_t u) {
    u = FindSet(u);
    return weight_[u];
  }

 private:
  std::vector<int32_t> parent_;
  std::vector<int32_t> rank_;
  std::vector<int64_t> weight_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  DSU dsu(n + 1);
  for (int i = 0; i < m; ++i) {
    int a = 0;
    std::cin >> a;
    if (a == 1) {
      int x = 0;
      int y = 0;
      int w = 0;
      std::cin >> x >> y >> w;
      dsu.Union(x, y, w);
    } else if (a == 2) {
      int x = 0;
      std::cin >> x;
      std::cout << dsu.Weight(x) << "\n";
    }
  }
}

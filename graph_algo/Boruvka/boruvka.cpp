#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
  Edge() = default;

  Edge(int64_t start, int64_t finish, int64_t w) : u(start), v(finish), weight(w) {
  }

  int64_t u;
  int64_t v;
  int64_t weight;
};

class DSU {
 public:
  explicit DSU(int64_t vertex) {
    parent_.resize(vertex);
    rank_.resize(vertex, 0);
    set_count_ = vertex;
    for (int64_t i = 0; i < vertex; ++i) {
      MakeSet(i);
    }
  }

  int64_t FindSet(int64_t x) const {
    while (x != parent_[x]) {
      x = parent_[x];
    }
    return x;
  }

  void Union(int64_t x, int64_t y) {
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
    --set_count_;
  }

  void MakeSet(int64_t x) {
    parent_[x] = x;
  }

  int64_t SetCount() const {
    return set_count_;
  }

 private:
  std::vector<int64_t> parent_;
  std::vector<int64_t> rank_;
  int64_t set_count_;
};

int64_t Boruvka(int64_t n, int64_t m, const std::vector<Edge>& edges) {
  DSU dsu(n);
  int64_t min_weight = 0;
  while (dsu.SetCount() > 1) {
    std::vector<int64_t> cheapest(n, -1);
    for (int64_t i = 0; i < m; ++i) {
      int64_t u = edges[i].u;
      int64_t v = edges[i].v;
      int64_t weight = edges[i].weight;
      int64_t set_u = dsu.FindSet(u);
      int64_t set_v = dsu.FindSet(v);
      if (set_u != set_v) {
        if (cheapest[set_u] == -1 || edges[cheapest[set_u]].weight > weight) {
          cheapest[set_u] = i;
        }
        if (cheapest[set_v] == -1 || edges[cheapest[set_v]].weight > weight) {
          cheapest[set_v] = i;
        }
      }
    }
    for (int64_t i = 0; i < n; ++i) {
      if (cheapest[i] != -1) {
        int64_t u = edges[cheapest[i]].u;
        int64_t v = edges[cheapest[i]].v;
        int64_t set_u = dsu.FindSet(u);
        int64_t set_v = dsu.FindSet(v);
        if (set_u != set_v) {
          min_weight += edges[cheapest[i]].weight;
          dsu.Union(set_u, set_v);
        }
      }
    }
  }
  return min_weight;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n >> m;
  std::vector<Edge> edges;
  for (int64_t i = 0; i < m; ++i) {
    int64_t u = 0;
    int64_t v = 0;
    int64_t w = 0;
    std::cin >> u >> v >> w;
    edges.emplace_back(u - 1, v - 1, w);
  }
  std::cout << Boruvka(n, m, edges) << "\n";
}

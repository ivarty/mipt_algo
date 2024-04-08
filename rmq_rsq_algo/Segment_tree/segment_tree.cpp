#include <sys/types.h>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <cmath>

class SegmentTree {
 public:
  SegmentTree() = default;

  explicit SegmentTree(const std::vector<int>& a) {
    int size = static_cast<int>(a.size());
    auto tsize = 1 << (static_cast<int>(std::log2(size)) + 1);
    size_ = tsize;
    t_.resize(2 * tsize - 1, {0, 0});
    for (int i = tsize - 1; i < tsize * 2 - 1; ++i) {
      if (i - tsize + 1 < size) {
        t_[i] = {a[i - tsize + 1], 1};
      }
    }
    for (int i = tsize - 2; i >= 0; --i) {
      auto leftson = t_[Left(i)];
      auto rightson = t_[Right(i)];
      if (leftson.first == rightson.first) {
        t_[i] = {leftson.first, leftson.second + rightson.second};
      } else if (leftson.first < rightson.first) {
        t_[i] = {rightson.first, rightson.second};
      } else {
        t_[i] = {leftson.first, leftson.second};
      }
    }
  }

  std::pair<int, int> Query(int l, int r) {
    return Query(l, r, 0, 0, size_ - 1);
  }

 private:
  int Parent(int i) {
    return (i - 1) / 2;
  }

  int Left(int i) {
    return 2 * i + 1;
  }

  int Right(int i) {
    return 2 * i + 2;
  }

  int IsLeftSon(int i) {
    return i % 2 == 1;
  }

  int IsRightSon(int i) {
    return i % 2 == 0;
  }

  std::pair<int, int> Query(int l, int r, int node, int a, int b) {
    if (a >= l && b <= r) {
      return t_[node];
    }
    if (a > r || b < l) {
      return {};
    }
    int middle = (a + b) / 2;
    auto leftres = Query(l, r, Left(node), a, middle);
    auto rightres = Query(l, r, Right(node), middle + 1, b);
    std::pair<int, int> answer = {0, 0};
    if (leftres.first == rightres.first) {
      answer = {leftres.first, leftres.second + rightres.second};
    } else if (leftres.first > rightres.first) {
      answer = leftres;
    } else {
      answer = rightres;
    }
    return answer;
  }

 private:
  std::vector<std::pair<int, int>> t_;
  int size_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  std::vector<int> subs(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> subs[i];
  }
  SegmentTree t(subs);
  int k = 0;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    int l = 0;
    int r = 0;
    std::cin >> l >> r;
    auto a = t.Query(--l, --r);
    std::cout << a.first << " " << a.second << "\n";
  }
}

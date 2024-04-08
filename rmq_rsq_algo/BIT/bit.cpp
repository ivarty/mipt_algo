#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class BIT {
 public:
  BIT() = default;

  explicit BIT(const std::vector<int64_t>& a) {
    auto size = static_cast<int64_t>(a.size());
    size_ = size;
    f_.resize(size, 0);
    std::vector<int64_t> p(size);
    p[0] = a[0];
    for (int64_t i = 1; i < size; ++i) {
      p[i] = p[i - 1] + a[i];
    }
    for (int64_t i = 0; i < size; ++i) {
      if ((i & (i + 1)) <= 1) {
        f_[i] = p[i];
      } else {
        f_[i] = p[i] - p[(i & (i + 1)) - 1];
      }
    }
  }

  int64_t Query(int64_t l, int64_t r) {
    return Query(r) - Query(l - 1);
  }

  void Update(int64_t k, int64_t delta) {
    for (int64_t i = k; i < size_; i = (i | (i + 1))) {
      f_[i] += delta;
    }
  }

 private:
  int64_t Query(int64_t k) {
    int64_t sum = 0;
    for (int64_t i = k; i >= 0; i = (i & (i + 1)) - 1) {
      sum += f_[i];
    }
    return sum;
  }

 private:
  std::vector<int64_t> f_;
  int64_t size_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  std::cin >> n;
  std::vector<int64_t> exhibit(n);
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> exhibit[i];
  }
  BIT bit(exhibit);
  int64_t m = 0;
  std::cin >> m;
  for (int64_t i = 0; i < m; ++i) {
    char a = 0;
    std::cin >> a;
    if (a == 's') {
      int64_t r = 0;
      int64_t l = 0;
      std::cin >> l >> r;
      std::cout << bit.Query(--l, --r) << " ";
    } else if (a == 'u') {
      int64_t k = 0;
      int64_t u = 0;
      std::cin >> k >> u;
      int64_t delta = u - exhibit[--k];
      exhibit[k] = u;
      bit.Update(k, delta);
    }
  }
  std::cout << "\n";
}

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>

std::vector<size_t> ZFunction(const std::string& s) {
  size_t size(s.size());
  std::vector<size_t> z(size, 0);
  z[0] = size;
  size_t left = 0;
  size_t right = 0;
  for (size_t i = 1; i < size; ++i) {
    if (i < right) {
      z[i] = std::min(z[i - left], right - i);
    }
    while ((i + z[i] < size) && (s[z[i]] == s[i + z[i]])) {
      ++z[i];
    }
    if (right < i + z[i]) {
      left = i;
      right = i + z[i];
    }
  }
  return z;
}

int main() {
  std::string s;
  std::cin >> s;
  auto z = ZFunction(s);
  for (const auto& a : z) {
    std::cout << a << " ";
  }
  std::cout << "\n";
}

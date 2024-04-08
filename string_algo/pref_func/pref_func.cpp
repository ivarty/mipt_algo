#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> PrefixFunction(const std::string& s) {
  size_t size = s.size();
  std::vector<int> p(size, 0);
  for (size_t i = 1; i < size; ++i) {
    int k = p[i - 1];
    while (s[i] != s[k] && k > 0) {
      k = p[k - 1];
    }
    if (s[i] == s[k]) {
      p[i] = k + 1;
    }
  }
  return p;
}

int main() {
  std::string s;
  std::cin >> s;
  auto p = PrefixFunction(s);
  for (const auto& a : p) {
    std::cout << a << " ";
  }
  std::cout << "\n";
}

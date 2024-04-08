#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> Zfunction(const std::string& s) {
  int size = static_cast<int>(s.size());
  std::vector<int> z(size, 0);
  int left = 0;
  int right = 0;
  for (int i = 1; i < size; ++i) {
    if (i < right) {
      z[i] = std::min(z[i - left], right - i);
    }
    while (i + z[i] < size && s[z[i]] == s[i + z[i]]) {
      ++z[i];
    }
    if (right < i + z[i]) {
      left = i;
      right = i + z[i];
    }
  }
  return z;
}

int SubstringCount(const std::string& s) {
  int count = 1;
  std::string substr;
  substr.push_back(s[0]);
  for (size_t i = 1; i < s.size(); ++i) {
    substr.push_back(s[i]);
    std::string rs(substr);
    std::reverse(rs.begin(), rs.end());
    auto z = Zfunction(rs);
    z[0] = 0;
    std::sort(z.begin(), z.end());
    count += static_cast<int>(rs.size()) - z[z.size() - 1];
  }
  return count;
}

int main() {
  std::string s;
  std::cin >> s;
  std::cout << SubstringCount(s) << "\n";
}

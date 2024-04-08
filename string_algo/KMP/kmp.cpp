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

std::vector<int> KMP(const std::string& s, const std::string& p) {
  std::string ps = p + '#' + s;
  auto prefix = PrefixFunction(ps);
  std::vector<int> answer;
  for (int i = 0; i < static_cast<int>(prefix.size()); ++i) {
    if (prefix[i] == static_cast<int>(p.size())) {
      answer.push_back(i - static_cast<int>(p.size()) * 2);
    }
  }
  return answer;
}

int main() {
  std::string s;
  std::string p;
  std::cin >> s >> p;
  auto answer = KMP(s, p);
  for (const auto& idx : answer) {
    std::cout << idx << "\n";
  }
}

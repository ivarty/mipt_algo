#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>

struct Node {
 public:
  Node() = default;

 public:
  std::map<char, int> dict;
  bool is_terminal = false;
};

class Trie {
 public:
  Trie() : root_(std::vector<Node>(1, Node())) {
  }

  void Insert(const std::string& s) {
    int current = 0;
    for (const auto& c : s) {
      int next = root_[current].dict[c];
      if (!next) {
        root_.emplace_back();
        root_[current].dict[c] = static_cast<int>(root_.size() - 1);
        next = root_[current].dict[c];
      }
      current = next;
    }
    root_[current].is_terminal = true;
  }

  bool Find(const std::string& s) {
    int current = 0;
    for (const auto& c : s) {
      if (!root_[current].dict[c]) {
        return false;
      }
      current = root_[current].dict[c];
    }
    return root_[current].is_terminal;
  }

 private:
  std::vector<Node> root_;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Trie trie;
  char a = 0;
  std::string s;
  while (std::cin >> a) {
    if (a == '+') {
      std::cin >> s;
      trie.Insert(s);
    }
    if (a == '?') {
      std::cin >> s;
      std::cout << (trie.Find(s) ? "YES\n" : "NO\n");
    }
    if (a == '#') {
      break;
    }
  }
}

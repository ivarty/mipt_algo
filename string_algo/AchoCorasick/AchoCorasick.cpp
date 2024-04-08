#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <queue>

struct Node {
 public:
  Node() = default;

 public:
  std::map<char, int> dict;
  bool is_terminal = false;
  int suffix_link;
  int exit_link;
};

class Trie {
 public:
  Trie() : root_(std::vector<Node>(1, Node())) {
  }

  explicit Trie(const std::vector<std::string>& patterns) {
    root_.resize(1, {});
    for (size_t i = 0; i < patterns.size(); ++i) {
      int node = Insert(patterns[i]);
      str_index_.insert({node, i});
      entries_.emplace_back();
    }
  }

  void BuildSuffixLinks() {
    int current = 0;
    root_[current].suffix_link = -1;
    std::queue<Queue> queue;
    for (const auto& a : root_[current].dict) {
      queue.emplace(a.first, current, a.second);
    }
    while (!queue.empty()) {
      auto q = queue.front();
      queue.pop();
      char s = q.symbol;
      int parent = q.root;
      int node = q.node;
      auto suff = root_[parent].suffix_link;
      while (suff != -1 && !root_[suff].dict.contains(s)) {
        suff = root_[suff].suffix_link;
      }
      root_[node].suffix_link = ((suff == -1) ? 0 : root_[suff].dict[s]);
      for (auto pair : root_[node].dict) {
        queue.emplace(pair.first, node, pair.second);
      }
    }
  }

  void BuildExitLinks() {
    int current = 0;
    root_[current].exit_link = -1;
    std::queue<int> queue;
    for (const auto& a : root_[current].dict) {
      queue.push(a.second);
    }
    while (!queue.empty()) {
      auto node = queue.front();
      queue.pop();
      auto suff = root_[node].suffix_link;
      if (node != 0 && suff != 0) {
        root_[node].exit_link = (root_[suff].is_terminal ? suff : root_[suff].exit_link);
      }
      for (const auto& neighbour : root_[node].dict) {
        queue.push(neighbour.second);
      }
    }
  }

  int NextState(int node, char symbol) {
    while (node != -1 && !root_[node].dict.contains(symbol)) {
      node = root_[node].suffix_link;
    }
    return (node == -1 ? 0 : root_[node].dict[symbol]);
  }

  void Entries(int idx, int node, const std::vector<std::string>& patterns) {
    if (!root_[node].is_terminal) {
      node = root_[node].exit_link;
    }
    while (node > 0) {
      auto string_i = str_index_[node];
      entries_[string_i].emplace_back(idx - patterns[string_i].size() + 2);
      node = root_[node].exit_link;
    }
  }

  void PrintEntries() {
    for (size_t i = 0; i < entries_.size(); ++i) {
      std::cout << entries_[i].size() << " ";
      if (!entries_[i].empty()) {
        for (size_t j = 0; j < entries_[i].size(); ++j) {
          std::cout << entries_[i][j] << " ";
        }
      }
      std::cout << "\n";
    }
  }

  int Insert(const std::string& s) {
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
    return current;
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
  class Queue {
   public:
    Queue() = default;

    Queue(char symbol, int root, int node) : symbol(symbol), root(root), node(node) {
    }

   public:
    char symbol;
    int root;
    int node;
  };

 private:
  std::vector<Node> root_;
  std::map<int, int> str_index_;
  std::vector<std::vector<int>> entries_;
};

void AchoCorasick(const std::string& s, const std::vector<std::string>& p) {
  Trie trie(p);
  trie.BuildSuffixLinks();
  trie.BuildExitLinks();
  int node = 0;
  for (size_t i = 0; i < s.size(); ++i) {
    node = trie.NextState(node, s[i]);
    trie.Entries(static_cast<int>(i), node, p);
  }
  trie.PrintEntries();
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string s;
  int n = 0;
  std::cin >> s;
  std::cin >> n;
  std::vector<std::string> patterns(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> patterns[i];
  }
  AchoCorasick(s, patterns);
}

#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <random>

struct Node {
  Node() = default;

  Node(int64_t x, int64_t y) : value(x), prioriy(y), size(1) {
  }

  int64_t value;
  int64_t prioriy;
  int64_t size;
  std::shared_ptr<Node> left;
  std::shared_ptr<Node> right;
  std::weak_ptr<Node> parent;
};

class Kurevo {
 public:
  Kurevo() = default;

  void Insert(int64_t x, int64_t y) {
    if (!Exists(tree_, x)) {
      PrivateInsert(x, y);
    }
  }

  void Delete(int64_t x) {
    if (Exists(tree_, x)) {
      Erase(x);
    }
  }

  bool Exists(int64_t x) {
    return Exists(tree_, x);
  }

  int64_t Next(int64_t x) {
    auto next = PrivateNext(x);
    return next ? next->value : 2000000000;
  }

  int64_t Prev(int64_t x) {
    auto prev = PrivatePrev(x);
    return prev ? prev->value : 2000000000;
  }

  int64_t Kth(int64_t k) {
    auto a = Get(tree_, k);
    return a ? a->value : 2000000000;
  }

 private:
  int64_t Size(std::shared_ptr<Node> node) {
    return node ? node->size : 0;
  }

  std::shared_ptr<Node> Get(std::shared_ptr<Node> root, int64_t k) {
    if (Size(root) <= k) {
      return nullptr;
    }
    while (true) {
      if (Size(root->left) < k) {
        k -= Size(root->left) + 1;
        root = root->right;
      } else if (Size(root->left) > k) {
        root = root->left;
      } else {
        return root;
      }
    }
  }

  void FixNode(std::shared_ptr<Node> t) {
    if (t) {
      t->size = 1;
      if (t->left) {
        t->size += t->left->size;
      }
      if (t->right) {
        t->size += t->right->size;
      }
    }
  }

  std::shared_ptr<Node> Merge(std::shared_ptr<Node> t1, std::shared_ptr<Node> t2) {
    if (!t1) {
      return t2;
    }
    if (!t2) {
      return t1;
    }
    if (t1->prioriy < t2->prioriy) {
      t1->right = Merge(t1->right, t2);
      t1->right->parent = t1;
      FixNode(t1);
      return t1;
    }
    t2->left = Merge(t1, t2->left);
    t2->left->parent = t2;
    FixNode(t2);
    return t2;
  }

  std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> Split(std::shared_ptr<Node> t, int64_t x) {
    if (!t) {
      return {nullptr, nullptr};
    }
    if (t->value < x) {
      auto result = Split(t->right, x);
      t->right = result.first;
      if (result.first) {
        result.first->parent = t;
      }
      if (result.second) {
        result.second->parent.reset();
      }
      FixNode(t);
      return {t, result.second};
    }
    auto result = Split(t->left, x);
    t->left = result.second;
    if (result.second) {
      result.second->parent = t;
    }
    if (result.first) {
      result.first->parent.reset();
    }
    FixNode(t);
    return {result.first, t};
  }

  void PrivateInsert(int64_t x, int64_t y) {
    Node node(x, y);
    auto result = Split(tree_, x);
    auto a = std::make_shared<Node>(node);
    tree_ = Merge(Merge(result.first, a), result.second);
  }

  void Erase(int64_t x) {
    auto split1 = Split(tree_, x);
    auto split2 = Split(split1.second, x + 1);
    tree_ = Merge(split1.first, split2.second);
  }

  bool Exists(std::shared_ptr<Node> t, int64_t x) {
    if (!t) {
      return false;
    }
    if (t->value == x) {
      return true;
    }
    if (t->value < x) {
      return Exists(t->right, x);
    }
    return Exists(t->left, x);
  }

  std::shared_ptr<Node> PrivateNext(int64_t x) {
    if (!tree_) {
      return nullptr;
    }
    auto split = Split(tree_, x + 1);
    if (!split.second) {
      return nullptr;
    }
    std::shared_ptr<Node> cur = split.second;
    while (cur->left) {
      cur = cur->left;
    }
    Merge(split.first, split.second);
    return cur;
  }

  std::shared_ptr<Node> PrivatePrev(int64_t x) {
    if (!tree_) {
      return nullptr;
    }
    auto split = Split(tree_, x);
    if (!split.first) {
      return nullptr;
    }
    std::shared_ptr<Node> cur = split.first;
    while (cur->right) {
      cur = cur->right;
    }
    Merge(split.first, split.second);
    return cur;
  }

 private:
  std::shared_ptr<Node> tree_;
};

int main() {
  Kurevo tree;
  std::string a;
  while (std::cin >> a) {
    if (a == "insert") {
      int64_t x = 0;
      int64_t y = std::rand();
      std::cin >> x;
      tree.Insert(x, y);
    }
    if (a == "delete") {
      int64_t x = 0;
      std::cin >> x;
      tree.Delete(x);
    }
    if (a == "exists") {
      int64_t x = 0;
      std::cin >> x;
      if (tree.Exists(x)) {
        std::cout << "true\n";
      } else {
        std::cout << "false\n";
      }
    }
    if (a == "next") {
      int64_t x = 0;
      std::cin >> x;
      int64_t next = tree.Next(x);
      if (next == 2000000000) {
        std::cout << "none\n";
      } else {
        std::cout << next << "\n";
      }
    }
    if (a == "prev") {
      int64_t x = 0;
      std::cin >> x;
      int64_t prev = tree.Prev(x);
      if (prev == 2000000000) {
        std::cout << "none\n";
      } else {
        std::cout << prev << "\n";
      }
    }
    if (a == "kth") {
      int64_t k = 0;
      std::cin >> k;
      int64_t kth = tree.Kth(k);
      if (kth == 2000000000) {
        std::cout << "none\n";
      } else {
        std::cout << kth << "\n";
      }
    }
  }
}

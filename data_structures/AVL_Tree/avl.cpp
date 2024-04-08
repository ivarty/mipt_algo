#include <iostream>

class Avl {
 private:
  struct Node {
    int64_t key;
    int height = 1;
    Node* left = nullptr;
    Node* right = nullptr;
  };

  Node* root_ = nullptr;

  Node* Balance(Node* p) {
    FixHeight(p);
    if (Bfactor(p) == 2) {
      if (Bfactor(p->right) == -1) {
        p->right = RotateRight(p->right);
      }
      return RotateLeft(p);
    }
    if (Bfactor(p) == -2) {
      if (Bfactor(p->left) == 1) {
        p->left = RotateLeft(p->left);
      }
      return RotateRight(p);
    }
    return p;
  }

  int Bfactor(const Node* node) const {
    return Height(node->right) - Height(node->left);
  }

  void FixHeight(Node* current) {
    current->height = std::max(Height(current->left), Height(current->right)) + 1;
  }

  void ClearNode(Node* current) {
    if (current == nullptr) {
      return;
    }
    ClearNode(current->left);
    ClearNode(current->right);
    delete current;
  }

  int Height(const Node* node) const {
    return node == nullptr ? 0 : node->height;
  }

  Node* RotateRight(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    FixHeight(p);
    FixHeight(q);
    return q;
  }

  Node* RotateLeft(Node* q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    FixHeight(q);
    FixHeight(p);
    return p;
  }

  Node* InsertNode(Node* r, int64_t k) {
    if (r == nullptr) {
      auto current = new Node;
      current->key = k;
      return current;
    }
    if (k < r->key) {
      r->left = InsertNode(r->left, k);
    } else {
      r->right = InsertNode(r->right, k);
    }
    return Balance(r);
  }

 public:
  int Height() const {
    return Height(root_);
  }

  void Clear() {
    ClearNode(root_);
  }

  void Insert(int64_t k) {
    root_ = InsertNode(root_, k);
  }

  int64_t Next(int64_t value) const {
    Node* current = root_;
    int64_t min = -1;
    while (current != nullptr) {
      if (value == current->key) {
        min = value;
        break;
      }
      if (value < current->key) {
        if (min > current->key || min < value) {
          min = current->key;
        }
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return min;
  }
};

int main() {
  int n;
  std::cin >> n;
  Avl s;
  char a;
  int64_t value;
  int64_t y = -1;
  int x = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> a >> value;
    if (a == '?') {
      if (s.Height() == 0) {
        std::cout << -1 << "\n";
        x = 1;
      } else {
        y = s.Next(value);
        std::cout << y << "\n";
        x = 1;
      }
    }
    if (a == '+' && x == 0) {
      s.Insert(value);
    } else if (a == '+' && x == 1) {
      s.Insert((value + y) % 1000000000);
      x = 0;
    }
  }
  s.Clear();
}

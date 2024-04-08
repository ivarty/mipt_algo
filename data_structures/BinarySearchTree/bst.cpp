#include <iostream>

template <typename T>
class BinarySearchTree {
 public:
  void Clear() {
    ClearNode(root_);
  }

  size_t Height() const {
    return height_;
  }

  void Insert(T value) {
    Node* parent = nullptr;
    Node* current = root_;
    size_t height = 1;
    while (current != nullptr) {
      parent = current;
      ++height;
      if (value < current->value) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    auto a = new Node{value, nullptr, nullptr, parent};
    if (parent == nullptr) {
      root_ = a;
      height_ = 1;
      return;
    }
    if (height > height_) {
      height_ = height;
    }
    if (a->value < parent->value) {
      parent->left = a;
      return;
    }
    parent->right = a;
  }

 private:
  struct Node {
    T value;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
  };

  Node* root_ = nullptr;
  size_t height_ = 0;

  void ClearNode(Node* current) {
    if (current == nullptr) {
      return;
    }
    ClearNode(current->left);
    ClearNode(current->right);
    delete current;
  }
};

int main() {
  int64_t value;
  std::cin >> value;
  BinarySearchTree<int64_t> s;
  while (value != 0) {
    s.Insert(value);
    std::cin >> value;
  }
  std::cout << s.Height() << "\n";
  s.Clear();
}

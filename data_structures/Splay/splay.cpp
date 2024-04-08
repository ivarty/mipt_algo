#include <algorithm>
#include <iostream>

class SplayTree {
 private:
  struct Node {
    int64_t key;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
  };

  struct Pair {
    Node* first;
    Node* second;
  };

  Node* root_ = nullptr;
  void SetParent(Node* child, Node* parent) {
    if (child != nullptr) {
      child->parent = parent;
    }
  }

  void KeepParent(Node* root) {
    SetParent(root->left, root);
    SetParent(root->right, root);
  }

  void Rotate(Node* child, Node* parent) {
    Node* gparent = parent->parent;
    if (gparent != nullptr) {
      if (gparent->left == parent) {
        gparent->left = child;
      } else {
        gparent->right = child;
      }
    }
    if (parent->left == child) {
      parent->left = child->right;
      child->right = parent;
    } else {
      parent->right = child->left;
      child->left = parent;
    }
    KeepParent(child);
    KeepParent(parent);
    SetParent(child, gparent);
  }

  Node* Splay(Node* root) {
    if (root->parent == nullptr) {
      return root;
    }
    Node* parent = root->parent;
    Node* gparent = parent->parent;
    if (gparent == nullptr) {
      Rotate(root, parent);
      return root;
    }
    if ((gparent->left == parent) == (parent->left == root)) {
      Rotate(parent, gparent);
      Rotate(root, parent);
    } else {
      Rotate(root, parent);
      Rotate(root, gparent);
    }
    return Splay(root);
  }

  Node* Find(Node* root, int64_t key) {
    if (root == nullptr) {
      return nullptr;
    }
    if (key < root->key && root->left != nullptr) {
      return Find(root->left, key);
    }
    if (key > root->key && root->right != nullptr) {
      return Find(root->right, key);
    }
    return Splay(root);
  }

  Pair* Split(Node* root, int64_t key) {
    auto ans = new Pair;
    if (root == nullptr) {
      ans->first = nullptr;
      ans->second = nullptr;
      return ans;
    }
    root = Find(root, key);
    if (root->key == key) {
      SetParent(root->left, nullptr);
      SetParent(root->right, nullptr);
      ans->first = root->left;
      ans->second = root->right;
      delete root;
      root_ = root;
      return ans;
    }
    if (root->key > key) {
      Node* left = root->left;
      root->left = nullptr;
      SetParent(left, nullptr);
      ans->first = left;
      ans->second = root;
      root_ = root;
      return ans;
    }
    Node* right = root->right;
    root->right = nullptr;
    SetParent(right, nullptr);
    ans->first = root;
    ans->second = right;
    root_ = root;
    return ans;
  }

  void ClearNode(Node* root) {
    if (root == nullptr) {
      return;
    }
    ClearNode(root->left);
    ClearNode(root->right);
    delete root;
  }

  Node* Next(Node* root, int64_t key) {
    if (root == nullptr) {
      return nullptr;
    }
    if (key < root->key && root->left != nullptr) {
      auto find = Next(root->left, key);
      return Splay(find->key < key ? root : find);
    }
    if (key > root->key && root->right != nullptr) {
      return Next(root->right, key);
    }
    return Splay(root);
  }

 public:
  void Insert(int64_t key) {
    auto child = Split(root_, key);
    auto ver = new Node;
    ver->key = key;
    ver->left = child->first;
    ver->right = child->second;
    KeepParent(ver);
    root_ = ver;
    delete child;
  }

  int64_t Next(int64_t key) {
    root_ = Next(root_, key);
    if ((root_ != nullptr && root_->key < key) || root_ == nullptr) {
      return -1;
    }
    return root_->key;
  }

  void Clear() {
    ClearNode(root_);
  }
};

int main() {
  int n;
  std::cin >> n;
  SplayTree s;
  char a;
  int64_t value;
  int64_t y = -1;
  int x = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> a >> value;
    if (a == '?') {
      y = s.Next(value);
      std::cout << y << "\n";
      x = 1;
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

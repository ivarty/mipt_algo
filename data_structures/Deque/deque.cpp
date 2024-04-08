#include <iostream>

struct Node {
  int64_t value;
  Node* next;
  Node* prev;
};

struct List {
  size_t size = 0;
  Node* head = nullptr;
  Node* tail = nullptr;
  void PushFront(int value) {
    auto new_node = new Node{value, head, nullptr};
    if (size == 0) {
      head = new_node;
      tail = new_node;
    } else {
      head->prev = new_node;
      head = new_node;
    }
    ++size;
  }

  void PushBack(int value) {
    auto* new_node = new Node{value, nullptr, tail};
    if (size == 0) {
      head = new_node;
      tail = new_node;
    } else {
      tail->next = new_node;
      tail = new_node;
    }
    ++size;
  }

  const int64_t& Front() const {
    return head->value;
  }

  const int64_t& Back() const {
    return tail->value;
  }

  int64_t PopFront() {
    auto* old_node = head;
    int64_t value = old_node->value;
    head = old_node->next;
    if (head != nullptr) {
      head->prev = nullptr;
    }
    delete old_node;
    --size;
    if (size == 0) {
      tail = nullptr;
    }
    return value;
  }

  int64_t PopBack() {
    auto* old_node = tail;
    int64_t value = old_node->value;
    tail = old_node->prev;
    if (tail != nullptr) {
      tail->next = nullptr;
    }
    delete old_node;
    --size;
    if (size == 0) {
      head = nullptr;
    }
    return value;
  }

  size_t Size() const {
    return size;
  }

  void Clear() {
    while (Size() > 0) {
      PopFront();
    }
  }
};

struct Dek {
  List dek;

  void PushFront(int64_t value) {
    return dek.PushFront(value);
  }
  void PushBack(int64_t value) {
    return dek.PushBack(value);
  }
  int64_t PopFront() {
    return dek.PopFront();
  }
  int64_t PopBack() {
    return dek.PopBack();
  }
  const int64_t& Front() const {
    return dek.Front();
  }
  const int64_t& Back() const {
    return dek.Back();
  }
  void Clear() {
    return dek.Clear();
  }
  size_t Size() const {
    return dek.Size();
  }
};

int Translate(char* a) {
  if (a[0] == 'f') {
    return 5;
  }
  if (a[0] == 'b') {
    return 6;
  }
  if (a[0] == 's') {
    return 7;
  }
  if (a[0] == 'c') {
    return 8;
  }
  if (a[0] == 'e') {
    return 9;
  }
  if (a[1] == 'u') {
    if (a[5] == 'f') {
      return 1;
    }
    return 2;
  }
  if (a[4] == 'f') {
    return 3;
  }
  return 4;
}

int main() {
  int n;
  int64_t value;
  std::cin >> n;
  Dek dek;
  char a[20];
  int trans;
  for (int i = 0; i < n; ++i) {
    std::cin >> a;
    trans = Translate(a);
    if (trans == 1) {
      std::cin >> value;
      dek.PushFront(value);
      std::cout << "ok\n";
    }
    if (trans == 2) {
      std::cin >> value;
      dek.PushBack(value);
      std::cout << "ok\n";
    }
    if (trans == 3) {
      if (dek.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << dek.PopFront() << "\n";
      }
    }
    if (trans == 4) {
      if (dek.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << dek.PopBack() << "\n";
      }
    }
    if (trans == 5) {
      if (dek.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << dek.Front() << "\n";
      }
    }
    if (trans == 6) {
      if (dek.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << dek.Back() << "\n";
      }
    }
    if (trans == 7) {
      std::cout << dek.Size() << "\n";
    }
    if (trans == 8) {
      dek.Clear();
      std::cout << "ok\n";
    }
    if (trans == 9) {
      dek.Clear();
      std::cout << "bye\n";
      return 0;
    }
  }
}

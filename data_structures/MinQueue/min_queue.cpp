#include <iostream>
#include <algorithm>

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

  int64_t& Back() const {
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

struct Stack {
  List list;
  void Push(int value) {
    list.PushBack(value);
  }

  int64_t& Top() const {
    return list.Back();
  }

  int64_t Pop() {
    return list.PopBack();
  }

  void Clear() {
    list.Clear();
  }

  size_t Size() const {
    return list.Size();
  }
};

struct Minstack {
  Stack stack_values;
  Stack stack_min;

  void Push(int64_t value) {
    stack_values.Push(value);
    if (stack_min.Size() == 0) {
      stack_min.Push(value);
    } else {
      stack_min.Push(std::min(value, stack_min.Top()));
    }
  }

  const int64_t& Top() const {
    return stack_values.Top();
  }

  int64_t Pop() {
    stack_min.Pop();
    return stack_values.Pop();
  }

  void Clear() {
    stack_min.Clear();
    stack_values.Clear();
  }

  size_t Size() const {
    return stack_values.Size();
  }

  int64_t Min() const {
    return stack_min.Top();
  }
};

struct MinQueue {
  Minstack stack1;
  Minstack stack2;

  void Push(int64_t value) {
    stack1.Push(value);
  }

  int64_t Pop() {
    if (stack2.Size() != 0) {
      return stack2.Pop();
    }
    while (stack1.Size() != 0) {
      stack2.Push(stack1.Pop());
    }
    return stack2.Pop();
  }

  int64_t Front() {
    if (stack2.Size() != 0) {
      return stack2.Top();
    }
    while (stack1.Size() != 0) {
      stack2.Push(stack1.Pop());
    }
    return stack2.Top();
  }

  int64_t Size() {
    return (stack1.Size() + stack2.Size());
  }

  void Clear() {
    stack1.Clear();
    stack2.Clear();
  }

  int64_t Min() {
    if (stack1.Size() == 0) {
      return stack2.Min();
    }
    if (stack2.Size() == 0) {
      return stack1.Min();
    }
    return (std::min(stack1.Min(), stack2.Min()));
  }
};

int Translator(char* a) {
  if (a[0] == 'e') {
    return 1;
  }
  if (a[0] == 'd') {
    return 2;
  }
  if (a[0] == 'f') {
    return 3;
  }
  if (a[0] == 's') {
    return 4;
  }
  if (a[0] == 'c') {
    return 5;
  }
  return 6;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  MinQueue s;
  int n;
  std::cin >> n;
  char a[15];
  int trans;
  int value;
  for (int i = 0; i < n; ++i) {
    std::cin >> a;
    trans = Translator(a);
    if (trans == 1) {
      std::cin >> value;
      s.Push(value);
      std::cout << "ok\n";
    }
    if (trans == 2) {
      if (s.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << s.Pop() << "\n";
      }
    }
    if (trans == 3) {
      if (s.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << s.Front() << "\n";
      }
    }
    if (trans == 4) {
      std::cout << s.Size() << "\n";
    }
    if (trans == 5) {
      s.Clear();
      std::cout << "ok\n";
    }
    if (trans == 6) {
      if (s.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << s.Min() << "\n";
      }
    }
  }
  s.Clear();
}

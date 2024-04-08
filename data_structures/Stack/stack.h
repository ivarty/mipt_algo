#ifndef STACK
#define STACK
#include <cstddef>
#include <deque>
#include <iterator>
#include <memory>
#include <type_traits>

template <class T, class Container = std::deque<T>>
class Stack {
 public:
  Stack() = default;

  explicit Stack(const Container& container) : container_(container) {
  }

  explicit Stack(Container&& container) : container_(std::move(container)) {
  }

  T& Top() {
    return container_.back();
  }

  const T& Top() const {
    return container_.back();
  }

  bool Empty() const {
    return container_.empty();
  }

  size_t Size() const {
    return container_.size();
  }

  void Push(const T& value) {
    container_.push_back(value);
  }

  void Push(T&& value) {
    container_.push_back(std::move(value));
  }

  void Pop() {
    container_.pop_back();
  }

  void Swap(Stack& other) {
    container_.swap(other.container_);
  }

  template <class... Args>
  void Emplace(Args&&... args) {
    container_.emplace_back(std::forward<Args>(args)...);
  }

  template <class InputIt>
  Stack(InputIt first, InputIt last) : container_(first, last) {
  }

 private:
  Container container_;
};

#endif

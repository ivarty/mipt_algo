#ifndef SHARED_PTR
#define SHARED_PTR
#include <utility>

template <class T>
class SharedPtr {
 public:
  SharedPtr();
  explicit SharedPtr(T* ptr);
  SharedPtr(std::nullptr_t);  // NOLINT
  SharedPtr(const SharedPtr& other);
  SharedPtr& operator=(const SharedPtr& other);
  SharedPtr(SharedPtr&& other) noexcept;
  SharedPtr& operator=(SharedPtr&& other) noexcept;
  ~SharedPtr();

  void Reset();
  void Reset(T* ptr);
  void Swap(SharedPtr<T>& other);

  T* Get() const;
  T* operator->() const;
  T& operator*() const;
  explicit operator bool() const;

  std::size_t UseCount() const;

 private:
  T* ptr_;
  std::size_t* strong_counter_;
};

template <class T>
SharedPtr<T>::SharedPtr() : ptr_(nullptr), strong_counter_(nullptr) {
}

template <class T>
SharedPtr<T>::SharedPtr(T* ptr) : ptr_(ptr), strong_counter_(new std::size_t(1)) {
}

template <class T>
SharedPtr<T>::SharedPtr(std::nullptr_t) : ptr_(nullptr), strong_counter_(nullptr) {
}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), strong_counter_(other.strong_counter_) {
  if (ptr_ != nullptr) {
    ++(*strong_counter_);
  }
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other) {
  if (this == &other) {
    return *this;
  }
  auto tmp = other;
  Swap(tmp);
  return *this;
}

template <class T>
SharedPtr<T>::SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), strong_counter_(other.strong_counter_) {
  other.ptr_ = nullptr;
  other.strong_counter_ = nullptr;
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  auto tmp = std::move(other);
  Swap(tmp);
  return *this;
}

template <class T>
SharedPtr<T>::~SharedPtr() {
  if (ptr_ != nullptr) {
    if (*strong_counter_ == 1) {
      delete ptr_;
      delete strong_counter_;
    } else {
      --(*strong_counter_);
    }
  }
}

template <class T>
void SharedPtr<T>::Reset(T* ptr) {
  SharedPtr<T> tmp(ptr);
  Swap(tmp);
}

template <class T>
void SharedPtr<T>::Reset() {
  SharedPtr<T> tmp(nullptr);
  Swap(tmp);
}

template <class T>
void SharedPtr<T>::Swap(SharedPtr<T>& other) {
  std::swap(ptr_, other.ptr_);
  std::swap(strong_counter_, other.strong_counter_);
}

template <class T>
T* SharedPtr<T>::Get() const {
  return ptr_;
}

template <class T>
T* SharedPtr<T>::operator->() const {
  return ptr_;
}

template <class T>
T& SharedPtr<T>::operator*() const {
  return *ptr_;
}

template <class T>
SharedPtr<T>::operator bool() const {
  return (Get() != nullptr);
}

template <class T>
std::size_t SharedPtr<T>::UseCount() const {
  if (strong_counter_ == nullptr) {
    return 0;
  }
  return *strong_counter_;
}
#endif

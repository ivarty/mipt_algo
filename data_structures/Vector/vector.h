#ifndef VECTOR
#define VECTOR
#define VECTOR_MEMORY_IMPLEMENTED
#include <cstddef>
#include <iostream>
#include <iterator>
#include <new>
#include <stdexcept>
#include <type_traits>
#include <initializer_list>
#include <utility>

template <class T>
class Vector {
 public:
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = size_t;

  template <bool IsConst>
  class ClassIterator;

  using Iterator = ClassIterator<false>;
  using ConstIterator = ClassIterator<true>;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

 public:
  Vector() : size_(0), capacity_(0), data_(nullptr) {
  }

  explicit Vector(SizeType size) : size_(size), capacity_(size) {
    data_ = static_cast<Pointer>(operator new(sizeof(ValueType) * capacity_));
    SizeType i = 0;
    try {
      for (; i < size_; ++i) {
        new (data_ + i) ValueType();
      }
    } catch (...) {
      Delete(i);
      throw;
    }
  }

  Vector(SizeType size, ValueType value) : size_(size), capacity_(size) {
    size == 0 ? data_ = nullptr : data_ = static_cast<Pointer>(operator new(sizeof(ValueType) * capacity_));
    SizeType i = 0;
    try {
      for (; i < size_; ++i) {
        new (data_ + i) ValueType(value);
      }
    } catch (...) {
      Delete(i);
      throw;
    }
  }

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator first, Iterator last) : size_(std::distance(first, last)), capacity_(size_) {
    if (size_ == 0) {
      data_ = nullptr;
    } else {
      data_ = static_cast<Pointer>(operator new(sizeof(ValueType) * capacity_));
    }
    SizeType i = 0;
    try {
      for (; i < size_; ++i) {
        new (data_ + i) ValueType(*first);
        ++first;
      }
    } catch (...) {
      Delete(i);
      throw;
    }
  }

  Vector(std::initializer_list<ValueType> list) : Vector(list.begin(), list.end()) {  // NOLINT
  }

  ~Vector() {
    Delete(size_);
  }

  Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) {
    other.size_ == 0 ? data_ = nullptr : data_ = static_cast<Pointer>(operator new(sizeof(ValueType) * capacity_));
    SizeType i = 0;
    try {
      for (; i < size_; ++i) {
        new (data_ + i) ValueType(other.data_[i]);
      }
    } catch (...) {
      Delete(i);
      throw;
    }
  }

  Vector(Vector&& other) : size_(other.size_), capacity_(other.capacity_) {
    other.size_ == 0 ? data_ = nullptr : data_ = other.data_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  Vector& operator=(const Vector& other) {
    if (this == &other) {
      return *this;
    }
    auto tmp = other;
    Swap(tmp);
    return *this;
  }

  Vector& operator=(Vector&& other) {
    if (this == &other) {
      return *this;
    }
    auto tmp = std::move(other);
    Swap(tmp);
    return *this;
  }

  SizeType Size() const {
    return size_;
  }

  SizeType Capacity() const {
    return capacity_;
  }

  bool Empty() const {
    return size_ == 0;
  }

  Reference operator[](SizeType i) {
    return data_[i];
  }

  ConstReference operator[](SizeType i) const {
    return data_[i];
  }

  Reference At(SizeType i) {
    if (i >= size_) {
      throw std::out_of_range("VectorOutOfRange");
    }
    return data_[i];
  }

  ConstReference At(SizeType i) const {
    if (i >= size_) {
      throw std::out_of_range("VectorOutOfRange");
    }
    return data_[i];
  }

  Reference Front() {
    return data_[0];
  }

  ConstReference Front() const {
    return data_[0];
  }

  Reference Back() {
    return data_[size_ - 1];
  }

  ConstReference Back() const {
    return data_[size_ - 1];
  }

  Pointer Data() {
    return data_;
  }

  ConstPointer Data() const {
    return data_;
  }

  void Swap(Vector& other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  void Resize(SizeType new_size) {
    if (new_size == size_) {
      return;
    }
    if (new_size < size_) {
      for (SizeType i = new_size; i < size_; ++i) {
        (data_ + i)->~ValueType();
      }
    }
    if (new_size > size_) {
      if (new_size > capacity_) {
        auto tmp = static_cast<Pointer>(operator new(sizeof(ValueType) * new_size));
        SizeType i = 0;
        try {
          for (; i < size_; ++i) {
            new (tmp + i) ValueType(std::move_if_noexcept(data_[i]));
          }
          for (; i < new_size; ++i) {
            new (tmp + i) ValueType();
          }
        } catch (...) {
          for (SizeType j = 0; j < i; ++j) {
            (tmp + j)->~ValueType();
          }
          operator delete(tmp);
          throw;
        }
        Delete(size_);
        capacity_ = new_size;
        std::swap(data_, tmp);
        if (tmp == nullptr) {
          operator delete(tmp);
        }
      } else {
        for (SizeType i = size_; i < new_size; ++i) {
          new (data_ + i) ValueType();
        }
      }
    }
    size_ = new_size;
  }

  void Resize(SizeType new_size, ConstReference value) {
    if (new_size == size_) {
      return;
    }
    if (new_size < size_) {
      for (SizeType i = new_size; i < size_; ++i) {
        (data_ + i)->~ValueType();
      }
    }
    if (new_size > size_) {
      if (new_size > capacity_) {
        auto tmp = static_cast<Pointer>(operator new(sizeof(ValueType) * new_size));
        SizeType i = 0;
        try {
          for (; i < size_; ++i) {
            new (tmp + i) ValueType(std::move_if_noexcept(data_[i]));
          }
          for (; i < new_size; ++i) {
            new (tmp + i) ValueType(std::move_if_noexcept(value));
          }
        } catch (...) {
          for (SizeType j = 0; j < i; ++j) {
            (tmp + j)->~ValueType();
          }
          operator delete(tmp);
          throw;
        }
        Delete(size_);
        capacity_ = new_size;
        std::swap(data_, tmp);
        if (tmp == nullptr) {
          operator delete(tmp);
        }
      } else {
        for (SizeType i = size_; i < new_size; ++i) {
          new (data_ + i) ValueType(std::move_if_noexcept(value));
        }
      }
    }
    size_ = new_size;
  }

  void Reserve(SizeType cap) {
    if (cap > capacity_) {
      Reallocation(cap);
    }
  }

  void ShrinkToFit() {
    if (size_ == 0) {
      operator delete(data_);
      data_ = nullptr;
    }
    if (size_ != capacity_) {
      Reallocation(size_);
    }
  }

  void Clear() {
    for (SizeType i = 0; i < size_; ++i) {
      (data_ + i)->~ValueType();
    }
    size_ = 0;
  }

  void PushBack(ConstReference value) {
    if (size_ == capacity_) {
      Reallocation(value);
    } else {
      try {
        new (data_ + size_) ValueType((value));
      } catch (...) {
        (data_ + size_)->~ValueType();
        throw;
      }
    }
    ++size_;
  }

  void PushBack(T&& value) {
    if (size_ == capacity_) {
      Reallocation(std::move(value));
    } else {
      try {
        new (data_ + size_) ValueType(std::move_if_noexcept(value));
      } catch (...) {
        (data_ + size_)->~ValueType();
        throw;
      }
    }
    ++size_;
  }

  void PopBack() {
    (data_ + size_ - 1)->~ValueType();
    --size_;
  }

  template <class... Args>
  void EmplaceBack(Args&&... args) {
    if (size_ == capacity_) {
      Reallocation();
    }
    new (data_ + size_) ValueType(std::forward<Args>(args)...);
    ++size_;
  }

  bool operator<(const Vector& other) const {
    for (SizeType i = 0; i < std::min(size_, other.size_); ++i) {
      if (data_[i] != other.data_[i]) {
        return data_[i] < other.data_[i];
      }
    }
    return size_ < other.size_;
  }

  Iterator begin() {  // NOLINT
    return Iterator(data_);
  }

  ConstIterator begin() const {  // NOLINT
    return ConstIterator(data_);
  }

  ConstIterator cbegin() const {  // NOLINT
    return begin();
  }

  Iterator end() {  // NOLINT
    return Iterator(data_ + size_);
  }

  ConstIterator end() const {  // NOLINT
    return ConstIterator(data_ + size_);
  }

  ConstIterator cend() const {  // NOLINT
    return end();
  }

  ReverseIterator rbegin() {  // NOLINT
    return static_cast<ReverseIterator>(end());
  }

  ReverseIterator rend() {  // NOLINT
    return static_cast<ReverseIterator>(begin());
  }

  ConstReverseIterator crbegin() const {  // NOLINT
    return static_cast<ConstReverseIterator>(cend());
  }

  ConstReverseIterator crend() const {  // NOLINT
    return static_cast<ConstReverseIterator>(cbegin());
  }

  ConstReverseIterator rbegin() const {  // NOLINT
    return static_cast<ConstReverseIterator>(cend());
  }

  ConstReverseIterator rend() const {  // NOLINT
    return static_cast<ConstReverseIterator>(cbegin());
  }

 public:
  template <bool IsConst>
  class ClassIterator {
   public:
    using difference_type = std::ptrdiff_t;                                         // NOLINT
    using pointer = Pointer;                                                        // NOLINT
    using value_type = ValueType;                                                   // NOLINT
    using reference = std::conditional_t<IsConst, const value_type&, value_type&>;  // NOLINT
    using iterator_category = std::random_access_iterator_tag;                      // NOLINT

    ClassIterator() = default;

    ClassIterator(const ClassIterator&) = default;

    explicit ClassIterator(Pointer ptr) : ptr_(ptr) {
    }

    ClassIterator& operator=(const ClassIterator&) = default;

    ClassIterator& operator++() {
      ++ptr_;
      return *this;
    }

    ClassIterator operator++(int)const {
      auto tmp = *this;
      return ++tmp;
    }

    ClassIterator& operator--() {
      --ptr_;
      return *this;
    }

    ClassIterator operator--(int)const {
      auto tmp = *this;
      return --tmp;
    }

    ClassIterator& operator+(SizeType n) {
      ptr_ += n;
      return *this;
    }

    ClassIterator operator+(SizeType n) const {
      auto tmp = ptr_ + n;
      return ClassIterator<IsConst>(tmp);
    }

    ClassIterator& operator-(SizeType n) {
      ptr_ -= n;
      return *this;
    }

    ClassIterator operator-(SizeType n) const {
      auto tmp = ptr_ - n;
      return ClassIterator<IsConst>(tmp);
    }

    reference operator*() const {
      return *ptr_;
    }

    bool operator==(const ClassIterator& other) const {
      return ptr_ == other.ptr_;
    }

    bool operator!=(const ClassIterator& other) const {
      return !(*this == other);
    }

   private:
    Pointer ptr_ = nullptr;
  };

 private:
  void Delete(SizeType count) {
    for (SizeType i = 0; i < count; ++i) {
      (data_ + i)->~ValueType();
    }
    operator delete(data_);
  }

  void Reallocation() {
    if (capacity_ == 0) {
      ++capacity_;
    }
    auto tmp = static_cast<Pointer>(operator new(sizeof(ValueType) * capacity_ * kMultiplyFactor));
    SizeType i = 0;
    try {
      for (; i < size_; ++i) {
        new (tmp + i) ValueType(std::move_if_noexcept(data_[i]));
      }
    } catch (...) {
      for (SizeType j = 0; j < i; ++j) {
        (tmp + j)->~ValueType();
      }
      operator delete(tmp);
      throw;
    }
    Delete(size_);
    capacity_ *= kMultiplyFactor;
    data_ = tmp;
  }

  template <class U>
  void Reallocation(U&& value) {
    if (capacity_ == 0) {
      ++capacity_;
    }
    auto tmp = static_cast<Pointer>(operator new(sizeof(ValueType) * capacity_ * kMultiplyFactor));
    SizeType i = 0;
    try {
      for (; i < size_; ++i) {
        new (tmp + i) ValueType(std::move_if_noexcept(data_[i]));
      }
      new (tmp + size_) ValueType(std::forward<U>(value));
      ++i;
    } catch (...) {
      for (SizeType j = 0; j < i; ++j) {
        (tmp + j)->~ValueType();
      }
      operator delete(tmp);
      throw;
    }
    Delete(size_);
    capacity_ *= kMultiplyFactor;
    std::swap(data_, tmp);
    if (tmp == nullptr) {
      operator delete(tmp);
    }
  }

  void Reallocation(SizeType size) {
    if (size == 0) {
      data_ = nullptr;
      size_ = 0;
      capacity_ = 0;
      return;
    }
    auto tmp = static_cast<Pointer>(operator new(sizeof(ValueType) * size));
    SizeType i = 0;
    try {
      for (; i < size_; ++i) {
        new (tmp + i) ValueType(std::move_if_noexcept(data_[i]));
      }
    } catch (...) {
      for (SizeType j = 0; j < i; ++j) {
        (tmp + j)->~ValueType();
      }
      operator delete(tmp);
      throw;
    }
    Delete(size_);
    capacity_ = size;
    std::swap(data_, tmp);
    if (tmp == nullptr) {
      operator delete(tmp);
    }
  }

 private:
  SizeType size_;
  SizeType capacity_;
  Pointer data_;
  static constexpr SizeType kMultiplyFactor = 2;
};

template <class T>
bool operator>(const Vector<T>& lhs, const Vector<T>& rhs) {
  return rhs < lhs;
}

template <class T>
bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs) {
  return !(rhs < lhs);
}

template <class T>
bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs) {
  return !(lhs < rhs);
}

template <class T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
  return !(lhs < rhs) && !(rhs < lhs);
}

template <class T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
  return (lhs < rhs) || (rhs < lhs);
}

#endif

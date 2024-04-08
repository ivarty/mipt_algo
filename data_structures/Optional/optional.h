#ifndef OPTIONAL
#define OPTIONAL

#include <cstddef>
#include <new>
#include <stdexcept>
#include <utility>
#include <optional>
#include <exception>

class BadOptionalAccess : public std::exception {
 public:
  const char* what() const noexcept override {
    return "Bad Optional Access";
  }
};

struct NulloptT {
  explicit NulloptT(int) {
  }
};

inline NulloptT nullopt = NulloptT(0);

struct InPlaceT {
  explicit InPlaceT() = default;
};

inline InPlaceT in_place{};

template <typename T>
class Optional {
 public:
  Optional() = default;
  Optional(NulloptT){};  // NOLINT

  Optional(const Optional& other) : has_value_(other.has_value_) {
    if (other.has_value_) {
      new (data_) T(*reinterpret_cast<const T*>(other.data_));
    }
  }

  Optional(Optional&& other) : has_value_(other.has_value_) {
    if (other.has_value_) {
      new (data_) T(std::move(*other));
    }
  }

  Optional(const T& value) : has_value_(true) {  // NOLINT
    new (data_) T(value);
  }

  Optional(T&& value) : has_value_(true) {  // NOLINT
    new (data_) T(std::move(value));
  }

  ~Optional() {
    Clear();
  }

  Optional& operator=(const Optional& other) {
    if (this == &other) {
      return *this;
    }
    Clear();
    if (!other.has_value_) {
      return *this;
    }
    new (data_) T(*reinterpret_cast<const T*>(other.data_));
    has_value_ = true;
    return *this;
  }

  Optional& operator=(Optional&& other) {
    if (this == &other) {
      return *this;
    }
    Clear();
    if (!other.has_value_) {
      return *this;
    }
    new (data_) T(*reinterpret_cast<T*>(std::move(other.data_)));
    has_value_ = true;
    return *this;
  }

  Optional& operator=(const T& value) {
    Clear();
    new (data_) T(value);
    has_value_ = true;
    return *this;
  }

  Optional& operator=(T&& value) {
    Clear();
    new (data_) T(std::move(value));
    has_value_ = true;
    return *this;
  }

  bool HasValue() const {
    return has_value_;
  }

  T& Value() & {
    if (!has_value_) {
      throw BadOptionalAccess();
    }
    return *reinterpret_cast<T*>(data_);
  }

  const T& Value() const & {
    if (!has_value_) {
      throw BadOptionalAccess();
    }
    return *reinterpret_cast<const T*>(data_);
  }

  T&& Value() && {
    if (!has_value_) {
      throw BadOptionalAccess();
    }
    return static_cast<T&&>(*reinterpret_cast<T*>(data_));
  }

  const T&& Value() const && {
    if (!has_value_) {
      throw BadOptionalAccess();
    }
    return static_cast<const T&&>(*reinterpret_cast<T*>(data_));
  }

  T& operator*() & {
    return *reinterpret_cast<T*>(data_);
  }

  const T& operator*() const & {
    return *reinterpret_cast<const T*>(data_);
  }

  T&& operator*() && {
    return static_cast<T&&>(*reinterpret_cast<T*>(data_));
  }

  const T&& operator*() const && {
    return static_cast<const T&&>(*reinterpret_cast<T*>(data_));
  }

  explicit operator bool() const {
    return has_value_;
  }

  void Reset() {
    Clear();
  }

  void Swap(Optional& other) {
    if (other.has_value_ && has_value_) {
      std::swap(other.Value(), Value());
    } else {
      std::swap(data_, other.data_);
    }
    std::swap(other.has_value_, has_value_);
  }

  template <typename... Args>
  void Emplace(Args&&... args) {
    Clear();
    new (data_) T(std::forward<Args>(args)...);
    has_value_ = true;
  }

 private:
  void Clear() {
    if (has_value_) {
      reinterpret_cast<T*>(data_)->~T();
      has_value_ = false;
    }
  }

 private:
  char data_[sizeof(T)];
  bool has_value_ = false;
};

#endif

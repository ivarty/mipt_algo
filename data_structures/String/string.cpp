#include "cppstring.h"

void String::Reallocation(int64_t size) {
  if (size < 0) {
    ++capacity_;
    capacity_ *= kMultiplyFactor;
  } else {
    capacity_ = size;
  }
  auto tmp = new char[capacity_];
  for (size_t i = 0; i < size_; ++i) {
    tmp[i] = array_[i];
  }
  delete[] array_;
  array_ = tmp;
}

String::String() : capacity_(0), array_(nullptr), size_(0) {
}

String::String(size_t size, const char symbol) : capacity_(size), size_(size) {
  if (size == 0) {
    array_ = nullptr;
  } else {
    array_ = new char[size];
  }
  for (size_t i = 0; i < size; ++i) {
    array_[i] = symbol;
  }
}

String::String(const char* string) : capacity_(strlen(string)), array_(new char[capacity_]), size_(capacity_) {
  for (size_t i = 0; i < size_; ++i) {
    array_[i] = string[i];
  }
}

String::String(const char* string, size_t size) : capacity_(size), array_(new char[size]), size_(size) {
  for (size_t i = 0; i < size_; ++i) {
    array_[i] = string[i];
  }
}

String::String(const String& other) : capacity_(other.capacity_), size_(other.size_) {
  other.size_ == 0 ? array_ = nullptr : array_ = new char[other.size_];
  for (size_t i = 0; i < size_; ++i) {
    array_[i] = other.array_[i];
  }
}

String& String::operator=(const String& other) {
  if (this == &other) {
    return *this;
  }
  auto tmp = other;
  Swap(tmp);
  return *this;
}

String::~String() {
  delete[] array_;
}

char& String::operator[](size_t i) {
  return array_[i];
}

const char& String::operator[](size_t i) const {
  return array_[i];
}

char& String::At(size_t i) {
  if (i >= size_) {
    throw StringOutOfRange{};
  }
  return array_[i];
}

const char& String::At(size_t i) const {
  if (i >= size_) {
    throw StringOutOfRange{};
  }
  return array_[i];
}

char& String::Front() {
  return array_[0];
}

const char& String::Front() const {
  return array_[0];
}

char& String::Back() {
  return array_[size_ - 1];
}

const char& String::Back() const {
  return array_[size_ - 1];
}

char* String::CStr() {
  return array_;
}

char* String::Data() {
  return array_;
}

const char* String::CStr() const {
  return array_;
}

const char* String::Data() const {
  return array_;
}

bool String::Empty() const {
  return size_ == 0;
}

size_t String::Size() const {
  return size_;
}

size_t String::Length() const {
  return size_;
}

size_t String::Capacity() const {
  return capacity_;
}

void String::Clear() {
  size_ = 0;
}

void String::Swap(String& other) {
  std::swap(array_, other.array_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

void String::PopBack() {
  array_[size_ - 1] = '\0';
  --size_;
}

void String::PushBack(const char& symbol) {
  if (size_ == capacity_) {
    Reallocation(-1);
  }
  array_[size_] = symbol;
  ++size_;
}

String& String::operator+=(const String& other) {
  for (size_t i = 0; i < other.size_; ++i) {
    PushBack(other.array_[i]);
  }
  return *this;
}

void String::Resize(size_t new_size, const char& symbol) {
  if (new_size > capacity_) {
    Reallocation(new_size);
  }
  if (new_size > size_) {
    for (size_t i = size_; i < new_size; ++i) {
      array_[i] = symbol;
    }
  }
  size_ = new_size;
}

void String::Reserve(size_t new_capacity) {
  Reallocation(std::max(new_capacity, capacity_));
}

void String::ShrinkToFit() {
  Reallocation(size_);
}

String operator+(const String& lhs, const String& rhs) {
  auto tmp = lhs;
  return tmp += rhs;
}

bool String::operator<(const String& other) const {
  for (size_t i = 0; i < std::min(size_, other.size_); ++i) {
    if (array_[i] != other.array_[i]) {
      return array_[i] < other.array_[i];
    }
  }
  return size_ < other.size_;
}

bool operator>(const String& lhs, const String& rhs) {
  return rhs < lhs;
}

bool operator>=(const String& lhs, const String& rhs) {
  return !(lhs < rhs);
}

bool operator<=(const String& lhs, const String& rhs) {
  return !(rhs < lhs);
}

bool operator==(const String& lhs, const String& rhs) {
  return !(lhs < rhs) && !(rhs < lhs);
}

bool operator!=(const String& lhs, const String& rhs) {
  return (lhs < rhs) || (rhs < lhs);
}

std::ostream& operator<<(std::ostream& out, const String& string) {
  for (size_t i = 0; i < string.size_; ++i) {
    out << string.array_[i];
  }
  return out;
}

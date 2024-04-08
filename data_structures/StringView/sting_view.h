#ifndef ARRAY
#define ARRAY
#include <iostream>
#include <stdexcept>
#include <cstring>

class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("StringViewOutOfRange") {
  }
};

class StringView {

 public:
  StringView();
  StringView(const char* str);  // NOLINT
  StringView(const char* str, size_t n);
  char operator[](size_t i) const;
  char At(size_t i) const;
  char Front() const;
  char Back() const;
  const char* Data() const;
  size_t Size() const;
  size_t Length() const;
  bool Empty() const;
  void Swap(StringView& other);
  void RemovePrefix(size_t prefix_size);
  void RemoveSuffix(size_t prefix_size);
  StringView Substr(size_t pos, size_t count);
  StringView Substr(size_t pos);

 private:
  size_t size_;
  const char* str_;
};

#endif

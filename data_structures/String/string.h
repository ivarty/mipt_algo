#ifndef STRING
#define STRING
#include <stdexcept>
#include <utility>
#include <iostream>
#include <cstring>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
 public:
  String();
  String(size_t size, char symbol);
  String(const char* string);  // NOLINT
  String(const char* string, size_t size);
  String(const String& other);
  ~String();

  String& operator=(const String& other);
  String& operator+=(const String& other);
  char& operator[](size_t i);
  const char& operator[](size_t i) const;
  bool operator<(const String& other) const;
  friend std::ostream& operator<<(std::ostream& out, const String& string);

  char& At(size_t i);
  const char& At(size_t i) const;

  char& Front();
  const char& Front() const;
  char& Back();
  const char& Back() const;

  char* CStr();
  char* Data();
  const char* CStr() const;
  const char* Data() const;

  bool Empty() const;
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;
  void Clear();

  void Swap(String& other);
  void PopBack();
  void PushBack(const char& symbol);
  void Resize(size_t new_size, const char& symbol);
  void Reserve(size_t new_capacity);
  void ShrinkToFit();

 private:
  void Reallocation(int64_t size);

 private:
  size_t capacity_;
  char* array_;
  size_t size_;
  inline static const size_t kMultiplyFactor = 2;
};

String operator+(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);
bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
#endif

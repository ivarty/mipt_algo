#include "string_view.h"

StringView::StringView() : size_(0), str_(nullptr) {
}

StringView::StringView(const char* str) : size_(strlen(str)), str_(str) {
}

StringView::StringView(const char* str, size_t n) : size_(n), str_(str) {
}

char StringView::operator[](size_t i) const {
  return str_[i];
}

char StringView::At(size_t i) const {
  if (i >= size_) {
    throw StringViewOutOfRange{};
  }
  return str_[i];
}

char StringView::Front() const {
  return *str_;
}

char StringView::Back() const {
  return str_[size_ - 1];
}

const char* StringView::Data() const {
  return str_;
}

size_t StringView::Size() const {
  return size_;
}

size_t StringView::Length() const {
  return size_;
}

bool StringView::Empty() const {
  return size_ == 0;
}

void StringView::Swap(StringView& other) {
  std::swap(str_, other.str_);
  std::swap(size_, other.size_);
}

void StringView::RemovePrefix(size_t prefix_size) {
  size_ = size_ - prefix_size;
  str_ = str_ + prefix_size;
}

void StringView::RemoveSuffix(size_t prefix_size) {
  size_ = size_ - prefix_size;
}

StringView StringView::Substr(size_t pos, size_t count) {
  if (pos > size_) {
    throw StringViewOutOfRange{};
  }
  StringView substr = *this;
  substr.RemoveSuffix(size_ - pos - std::min(count, size_ - pos));
  substr.RemovePrefix(pos);
  return substr;
}

StringView StringView::Substr(size_t pos) {
  size_t count = -1;
  if (pos > size_) {
    throw StringViewOutOfRange{};
  }
  StringView substr = *this;
  substr.RemoveSuffix(size_ - pos - std::min(count, size_ - pos));
  substr.RemovePrefix(pos);
  return substr;
}

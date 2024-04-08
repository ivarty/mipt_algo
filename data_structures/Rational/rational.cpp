#include "rational.h"
void Rational::Sokrat() {
  int32_t gcd = std::gcd(den_, num_);
  den_ = den_ / gcd;
  num_ = num_ / gcd;
  if (den_ < 0) {
    den_ *= -1;
    num_ *= -1;
  }
}

Rational::Rational() : num_(0), den_(1) {
}

Rational::Rational(int32_t value) : num_(value), den_(1) {
}

Rational::Rational(int32_t x, int32_t y) : num_(x), den_(y) {
  if (den_ == 0) {
    throw RationalDivisionByZero{};
  }
  Sokrat();
}

const int32_t& Rational::GetNumerator() const {
  return num_;
}

const int32_t& Rational::GetDenominator() const {
  return den_;
}

void Rational::SetNumerator(int32_t num) {
  num_ = num;
  Sokrat();
}

void Rational::SetDenominator(int32_t den) {
  if (den == 0) {
    throw RationalDivisionByZero{};
  }
  den_ = den;
  Sokrat();
}

Rational& Rational::operator+=(const Rational& q) {
  num_ = num_ * q.den_ + den_ * q.num_;
  den_ = den_ * q.den_;
  Sokrat();
  return *this;
}

Rational& Rational::operator-=(const Rational& q) {
  num_ = num_ * q.den_ - den_ * q.num_;
  den_ = den_ * q.den_;
  Sokrat();
  return *this;
}

Rational& Rational::operator*=(const Rational& q) {
  num_ = num_ * q.num_;
  den_ = den_ * q.den_;
  Sokrat();
  return *this;
}

Rational& Rational::operator/=(const Rational& q) {
  if (q.num_ == 0) {
    throw RationalDivisionByZero{};
  }
  num_ = num_ * q.den_;
  den_ = den_ * q.num_;
  Sokrat();
  return *this;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
  Rational tmp = lhs;
  return tmp += rhs;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
  Rational tmp = lhs;
  return tmp -= rhs;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
  Rational tmp = lhs;
  return tmp *= rhs;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
  Rational tmp = lhs;
  return tmp /= rhs;
}

Rational Rational::operator+() const {
  return *this;
}

Rational Rational::operator-() const {
  Rational tmp = *this;
  tmp.num_ *= -1;
  return tmp;
}

Rational& Rational::operator++() {
  num_ += den_;
  return *this;
}

Rational& Rational::operator--() {
  num_ -= den_;
  return *this;
}

Rational Rational::operator++(int) {
  Rational old = *this;
  num_ += den_;
  return old;
}

Rational Rational::operator--(int) {
  Rational old = *this;
  num_ -= den_;
  return old;
}

bool Rational::operator<(const Rational& lhs) const {
  return this->num_ * lhs.GetDenominator() < lhs.GetNumerator() * this->den_;
}

bool operator>(const Rational& lhs, const Rational& rhs) {
  return rhs < lhs;
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
  return !(lhs < rhs);
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
  return !(rhs < lhs);
}

bool operator==(const Rational& lhs, const Rational& rhs) {
  return !(lhs < rhs) && !(rhs < lhs);
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
  return (lhs < rhs) || (rhs < lhs);
}

std::istream& operator>>(std::istream& in, Rational& q) {
  int32_t numerator = 0;
  int32_t denominator = 1;
  in >> numerator;
  if (in.peek() == '/') {
    in.get();
    in >> denominator;
  }
  q = Rational(numerator, denominator);
  return in;
}

std::ostream& operator<<(std::ostream& out, const Rational& q) {
  if (q.den_ == 1) {
    out << q.num_;
    return out;
  }
  out << q.num_ << '/' << q.den_;
  return out;
}

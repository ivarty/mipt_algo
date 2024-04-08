#ifndef RATIONAL
#define RATIONAL
#include <stdexcept>
#include <numeric>
#include <iostream>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
 public:
  Rational();
  Rational(int32_t value);  // NOLINT
  Rational(int32_t x, int32_t y);
  const int32_t& GetNumerator() const;
  const int32_t& GetDenominator() const;
  void SetNumerator(int32_t);
  void SetDenominator(int32_t);
  Rational& operator+=(const Rational& q);
  Rational& operator-=(const Rational& q);
  Rational& operator*=(const Rational& q);
  Rational& operator/=(const Rational& q);
  Rational operator+() const;
  Rational operator-() const;
  Rational& operator++();  // pre
  Rational& operator--();
  Rational operator++(int);  // post
  Rational operator--(int);
  bool operator<(const Rational& lhs) const;
  friend std::ostream& operator<<(std::ostream& out, const Rational& q);
  friend std::istream& operator>>(std::istream& in, Rational& q);

 private:
  int32_t num_;
  int32_t den_;
  void Sokrat();
};

Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);
bool operator>(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);
bool operator==(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
#endif

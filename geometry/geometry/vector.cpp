#include <cstdint>
#include <iostream>
#include "../vector.h"
#include "../point.h"
namespace geometry {
Vector::Vector() = default;

Vector::Vector(const Point& point1, const Point& point2)
    : x_(point2.Xc() - point1.Xc()), y_(point2.Yc() - point1.Yc()) {
}

Vector::Vector(int64_t x, int64_t y) : x_(x), y_(y) {
}

Vector& Vector::operator+=(const Vector& other) {
  x_ += other.x_;
  y_ += other.y_;
  return *this;
}

Vector& Vector::operator-=(const Vector& other) {
  x_ -= other.x_;
  y_ -= other.y_;
  return *this;
}

Vector& Vector::operator*=(const int64_t& other) {
  x_ *= other;
  y_ *= other;
  return *this;
}

Vector& Vector::operator/=(const int64_t& other) {
  x_ /= other;
  y_ /= other;
  return *this;
}

Vector Vector::operator+() const {
  return *this;
}

Vector Vector::operator-() const {
  auto tmp = *this;
  tmp.x_ *= -1;
  tmp.y_ *= -1;
  return tmp;
}

Vector operator+(const Vector& lhs, const Vector& rhs) {
  auto tmp = lhs;
  return tmp += rhs;
}

Vector operator-(const Vector& lhs, const Vector& rhs) {
  auto tmp = lhs;
  return tmp -= rhs;
}

Vector operator*(const Vector& lhs, const int64_t& rhs) {
  auto tmp = lhs;
  return tmp *= rhs;
}

Vector operator/(const Vector& lhs, const int64_t& rhs) {
  auto tmp = lhs;
  return tmp /= rhs;
}

bool operator==(const Vector& lhs, const Vector& rhs) {
  return (lhs.Xc() == rhs.Xc() && lhs.Yc() == rhs.Yc());
}

int64_t ScalarProduct(const Vector& vector1, const Vector& vector2) {
  return vector1.Xc() * vector2.Xc() + vector1.Yc() * vector2.Yc();
}

int64_t VectorProduct(const Vector& vector1, const Vector& vector2) {
  return vector1.Xc() * vector2.Yc() - vector1.Yc() * vector2.Xc();
}

int64_t Vector::Xc() const {
  return x_;
}

int64_t Vector::Yc() const {
  return y_;
}

}  // namespace geometry

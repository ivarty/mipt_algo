#ifndef VECTOR
#define VECTOR
#include <cstdint>
#include <iostream>

namespace geometry {
class Point;
class Vector {
 public:
  Vector();
  Vector(const Point& point1, const Point& point2);
  Vector(int64_t x, int64_t y);

  Vector& operator+=(const Vector& other);
  Vector& operator-=(const Vector& other);
  Vector& operator*=(const int64_t& other);
  Vector& operator/=(const int64_t& other);
  Vector operator+() const;
  Vector operator-() const;

  int64_t Xc() const;
  int64_t Yc() const;

 private:
  int64_t x_;
  int64_t y_;
};

Vector operator+(const Vector& lhs, const Vector& rhs);
Vector operator-(const Vector& lhs, const Vector& rhs);
Vector operator*(const Vector& lhs, const int64_t& rhs);
Vector operator/(const Vector& lhs, const int64_t& rhs);

bool operator==(const Vector& lhs, const Vector& rhs);
int64_t ScalarProduct(const Vector& vector1, const Vector& vector2);
int64_t VectorProduct(const Vector& vector1, const Vector& vector2);
}  // namespace geometry

#endif

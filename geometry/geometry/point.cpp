#include "../point.h"
#include "../vector.h"
#include "../segment.h"
#include <cstdint>
#include <iostream>
#include <memory>
namespace geometry {
Vector operator-(const Point& lhs, const Point& rhs) {
  Vector a(rhs, lhs);
  return a;
}

Point::Point() = default;

Point::Point(int64_t x, int64_t y) : x_(x), y_(y) {
}

IShape& Point::Move(const Vector& vector) {
  x_ += vector.Xc();
  y_ += vector.Yc();
  return *this;
}

bool Point::ContainsPoint(const Point& point) const {
  return (point.x_ == x_ && y_ == point.y_);
}

bool Point::CrossesSegment(const Segment& segment) const {
  const auto tmp = *this;
  Vector ac(segment.Ap(), tmp);
  Vector cb(tmp, segment.Bp());
  return (VectorProduct(ac, cb) == 0 && ScalarProduct(ac, cb) >= 0);
}

std::shared_ptr<IShape> Point::Clone() const {
  return std::make_shared<Point>(x_, y_);
}

std::string Point::ToString() const {
  return "Point(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
}

int64_t Point::Xc() const {
  return x_;
}

int64_t Point::Yc() const {
  return y_;
}
}

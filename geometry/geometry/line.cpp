#include "../line.h"
#include "../segment.h"
#include <cstdint>
#include <iostream>
#include <memory>

namespace geometry {
Line::Line() = default;

Line::Line(int64_t a, int64_t b, int64_t c) : a_(a), b_(b), c_(c) {
}

Line::Line(const Point& x, const Point& y) {
  a_ = y.Yc() - x.Yc();
  b_ = -(y.Xc() - x.Xc());
  c_ = x.Yc() * (-b_) - x.Xc() * a_;
  vector_ = Vector(x, y);
  point_ = x;
  point2_ = y;
}

IShape& Line::Move(const Vector& vec) {
  c_ -= a_ * vec.Xc() + b_ * vec.Yc();
  return *this;
}

bool Line::ContainsPoint(const Point& point) const {
  return (a_ * point.Xc() + b_ * point.Yc() + c_ == 0);
}

bool Line::CrossesSegment(const Segment& segment) const {
  return ((a_ * segment.Ap().Xc() + b_ * segment.Ap().Yc() + c_) *
              (a_ * segment.Bp().Xc() + b_ * segment.Bp().Yc() + c_) <=
          0);
}

std::shared_ptr<IShape> Line::Clone() const {
  return std::make_shared<Line>(a_, b_, c_);
}

std::string Line::ToString() const {
  return "Line(" + std::to_string(a_) + ", " + std::to_string(b_) + ", " + std::to_string(c_) + ")";
}

int64_t Line::Acf() const {
  return a_;
}

int64_t Line::Bcf() const {
  return b_;
}

int64_t Line::Ccf() const {
  return c_;
}

Vector Line::Vec() const {
  return vector_;
}

Point Line::P1() const {
  return point_;
}

Point Line::P2() const {
  return point2_;
}
}  // namespace geometry

#include <cmath>
#include <iostream>
#include <memory>
#include "../circle.h"
#include "../segment.h"
#include "../line.h"
#include "../ishape.h"

namespace geometry {
Circle::Circle() = default;

Circle::Circle(const Point& point, int64_t value) : centre_(point), radius_(value) {
}

IShape& Circle::Move(const Vector& vector) {
  centre_.Move(vector);
  return *this;
}

bool Circle::ContainsPoint(const Point& point) const {
  Vector a(centre_, point);
  return (ScalarProduct(a, a) <= radius_ * radius_);
}

bool Circle::CrossesSegment(const Segment& segment) const {
  Vector ca(centre_, segment.Ap());
  Vector cb(centre_, segment.Bp());
  int64_t a = ScalarProduct(ca, ca) - radius_ * radius_;
  int64_t b = ScalarProduct(cb, cb) - radius_ * radius_;
  if (a * b <= 0) {
    return true;
  }
  Vector ab(segment.Ap(), segment.Bp());
  a = ScalarProduct(ab, ab);
  b = 2 * ScalarProduct(ab, ca);
  Point o(0, 0);
  Vector oc(o, centre_);
  Vector oa(o, segment.Ap());
  int64_t c = ScalarProduct(oc, oc) + ScalarProduct(oa, oa) - 2 * ScalarProduct(oc, oa) - radius_ * radius_;
  if (b * b - 4 * a * c < 0) {
    return false;
  }
  double x = std::sqrt(b * b - 4 * a * c) - b;
  if (std::abs(x) > 2 * std::abs(a)) {
    return false;
  }
  x = -std::sqrt(b * b - 4 * a * c) - b;
  return !(std::abs(x) > 2 * std::abs(a));
}

std::shared_ptr<IShape> Circle::Clone() const {
  return (std::make_shared<Circle>(centre_, radius_));
}

std::string Circle::ToString() const {
  return "Circle(" + centre_.ToString() + ", " + std::to_string(radius_) + ")";
}

}  // namespace geometry

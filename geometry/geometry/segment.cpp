#include <iostream>
#include <memory>
#include "../segment.h"
#include "../line.h"

namespace geometry {

bool SegmentCrossLine(const Line& line, const Segment& segment) {
  Vector ab = line.Vec();
  Vector ac(line.P1(), segment.Ap());
  Vector ad(line.P1(), segment.Bp());
  Vector cd(segment.Ap(), segment.Bp());
  Vector cb(segment.Ap(), line.P2());
  Vector ca(segment.Ap(), line.P1());
  return (VectorProduct(ab, ac) * VectorProduct(ab, ad) <= 0 && VectorProduct(cd, ca) * VectorProduct(cd, cb) <= 0);
}

Segment::Segment() = default;

Segment::Segment(const Point& x, const Point& y) : a_(x), b_(y) {
}

IShape& Segment::Move(const Vector& vector) {
  a_.Move(vector);
  b_.Move(vector);
  return *this;
}

bool Segment::ContainsPoint(const Point& point) const {
  Vector ac(a_, point);
  Vector cb(point, b_);
  return (VectorProduct(ac, cb) == 0 && ScalarProduct(ac, cb) >= 0);
}

bool Segment::CrossesSegment(const Segment& segment) const {
  Vector ab(a_, b_);
  Vector ac(a_, segment.Ap());
  Vector ad(a_, segment.Bp());
  Vector cd(segment.Ap(), segment.Bp());
  Vector cb(segment.Ap(), b_);
  Vector ca(segment.Ap(), a_);
  Line line(a_, b_);
  if (VectorProduct(ab, ac) == 0 && VectorProduct(ab, ad) == 0 && VectorProduct(cd, ca) == 0 &&
      VectorProduct(cd, cb) == 0) {
    return (ContainsPoint(segment.Ap()) || ContainsPoint(segment.Bp()) || segment.ContainsPoint(a_) ||
            segment.ContainsPoint(b_));
  }
  return SegmentCrossLine(line, segment);
}

std::shared_ptr<IShape> Segment::Clone() const {
  return (std::make_shared<Segment>(a_, b_));
}

std::string Segment::ToString() const {
  return "Segment(" + a_.ToString() + ", " + b_.ToString() + ")";
}

Point Segment::Ap() const {
  return a_;
}

Point Segment::Bp() const {
  return b_;
}
}  // namespace geometry

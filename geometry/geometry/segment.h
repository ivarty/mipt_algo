#ifndef SEGMENT
#define SEGMENT

#include "ishape.h"
#include "point.h"

namespace geometry {
class Segment : public IShape {
 public:
  Segment();
  Segment(const Point& x, const Point& y);
  IShape& Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  std::shared_ptr<IShape> Clone() const override;
  std::string ToString() const override;

  Point Ap() const;
  Point Bp() const;

 private:
  Point a_;
  Point b_;
};
}  // namespace geometry

#endif

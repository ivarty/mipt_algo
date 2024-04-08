#ifndef POINT
#define POINT
#include <cstdint>
#include "ishape.h"
#include "vector.h"

namespace geometry {
class Point : public IShape {
 public:
  Point();
  Point(int64_t x, int64_t y);
  IShape& Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  std::shared_ptr<IShape> Clone() const override;
  std::string ToString() const override;
  int64_t Xc() const;
  int64_t Yc() const;

 private:
  int64_t x_;
  int64_t y_;
};

Vector operator-(const Point& lhs, const Point& rhs);
}  // namespace geometry

#endif

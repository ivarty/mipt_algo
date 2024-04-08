#ifndef RAY
#define RAY

#include "ishape.h"
#include "point.h"
#include "vector.h"

namespace geometry {
class Ray : public IShape {
 public:
  Ray();
  Ray(const Point& x, const Point& y);
  Ray(const Point& point, const Vector& vector);
  IShape& Move(const Vector& vec) override;
  bool ContainsPoint(const Point& p) const override;
  bool CrossesSegment(const Segment& segment) const override;
  std::shared_ptr<IShape> Clone() const override;
  std::string ToString() const override;

 private:
  Vector vector_;
  Point point_;
  Point point2_;
};
}  // namespace geometry

#endif

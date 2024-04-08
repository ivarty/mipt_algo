#ifndef POLYGON
#define POLYGON

#include "ishape.h"
#include "point.h"
#include <vector>

namespace geometry {
class Polygon : public IShape {
 public:
  Polygon();
  explicit Polygon(const std::vector<Point>& other);
  IShape& Move(const Vector& vector) override;
  bool ContainsPoint(const Point& p) const override;
  bool CrossesSegment(const Segment& segment) const override;
  std::shared_ptr<IShape> Clone() const override;
  std::string ToString() const override;

 private:
  bool PointOnPolygon(const Point& p) const;

 private:
  std::vector<Point> vertices_;
};
}  // namespace geometry

#endif

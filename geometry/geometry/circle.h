#ifndef CIRCLE
#define CIRCLE
#include "ishape.h"
#include "point.h"

namespace geometry {
class Circle : public IShape {
 public:
  Circle();
  Circle(const Point& point, const int64_t value);
  IShape& Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  std::shared_ptr<IShape> Clone() const override;
  std::string ToString() const override;

 private:
  Point centre_;
  int64_t radius_;
};
}  // namespace geometry

#endif

#ifndef ISHAPE
#define ISHAPE

#include <memory>
#include <string>

namespace geometry {
class Point;
class Segment;
class Vector;

class IShape {
 public:
  virtual ~IShape() = default;
  virtual IShape& Move(const Vector& vector) = 0;
  virtual bool ContainsPoint(const Point& point) const = 0;
  virtual bool CrossesSegment(const Segment& segment) const = 0;
  virtual std::shared_ptr<IShape> Clone() const = 0;
  virtual std::string ToString() const = 0;
};
}  // namespace geometry

#endif

#ifndef LINE
#define LINE

#include <cstdint>
#include "ishape.h"
#include "point.h"

namespace geometry {
class Line : public IShape {
 public:
  Line();
  Line(int64_t a, int64_t b, int64_t c);
  Line(const Point& x, const Point& y);
  IShape& Move(const Vector& vec) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  std::shared_ptr<IShape> Clone() const override;
  std::string ToString() const override;

  int64_t Acf() const;
  int64_t Bcf() const;
  int64_t Ccf() const;
  Vector Vec() const;
  Point P1() const;
  Point P2() const;

 private:
  int64_t a_;
  int64_t b_;
  int64_t c_;
  Vector vector_;
  Point point_;
  Point point2_;
};
}  // namespace geometry

#endif

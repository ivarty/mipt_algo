#include "../ray.h"
#include "../segment.h"
#include "../line.h"
#include <iostream>
#include <memory>

namespace geometry {
Ray::Ray() = default;

Ray::Ray(const Point& x, const Point& y) : vector_(Vector(x, y)), point_(x), point2_(y) {
}

Ray::Ray(const Point& point, const Vector& vector) : vector_(vector), point_(point) {
}

IShape& Ray::Move(const Vector& vec) {
  point_.Move(vec);
  point2_.Move(vec);
  return *this;
}

bool Ray::ContainsPoint(const Point& p) const {
  Vector point_vector(point_, p);
  return (ScalarProduct(vector_, point_vector) >= 0 && VectorProduct(vector_, point_vector) == 0);
}

bool Ray::CrossesSegment(const Segment& segment) const {
  Line line(point_, point2_);
  Vector ao(segment.Ap(), point_);
  Vector ab(segment.Ap(), segment.Bp());
  return ((line.CrossesSegment(segment)) && (VectorProduct(ao, ab) * VectorProduct(vector_, ab) <= 0));
}

std::shared_ptr<IShape> Ray::Clone() const {
  return std::make_shared<Ray>(point_, vector_);
}

std::string Ray::ToString() const {
  return "Ray(" + point_.ToString() + ", Vector(" + std::to_string(vector_.Xc()) + ", " + std::to_string(vector_.Yc()) +
         "))";
}

}  // namespace geometry

#include "../polygon.h"
#include "../segment.h"
#include <iostream>
#include <memory>

namespace geometry {

bool Polygon::PointOnPolygon(const Point& p) const {
  size_t size = vertices_.size();
  for (size_t i = 0; i < size; ++i) {
    Segment side(vertices_[i], vertices_[(i + 1) % size]);
    if (p.CrossesSegment(side)) {
      return true;
    }
  }
  return false;
}

Polygon::Polygon() = default;

Polygon::Polygon(const std::vector<Point>& other) {
  size_t size = other.size();
  for (size_t i = 0; i < size; ++i) {
    vertices_.push_back(other[i]);
  }
}

IShape& Polygon::Move(const Vector& vector) {
  size_t size = vertices_.size();
  for (size_t i = 0; i < size; ++i) {
    vertices_[i].Move(vector);
  }
  return *this;
}

bool Polygon::ContainsPoint(const Point& p) const {
  const int64_t x = 2e9;
  Point inf(x, p.Yc() + 1);
  Segment ab(p, inf);
  int k = 0;
  size_t size = vertices_.size();
  if (PointOnPolygon(p)) {
    return true;
  }
  for (size_t i = 0; i < size; ++i) {
    Segment side(vertices_[i], vertices_[(i + 1) % size]);
    if (ab.CrossesSegment(side)) {
      ++k;
    }
  }
  return (k % 2 != 0);
}

bool Polygon::CrossesSegment(const Segment& segment) const {
  size_t size = vertices_.size();
  for (size_t i = 0; i < size; ++i) {
    Segment side(vertices_[i], vertices_[(i + 1) % size]);
    if (side.CrossesSegment(segment)) {
      return true;
    }
  }
  return false;
}

std::shared_ptr<IShape> Polygon::Clone() const {
  return (std::make_shared<Polygon>(vertices_));
}

std::string Polygon::ToString() const {
  std::string object = "Polygon(";
  size_t size = vertices_.size();
  for (size_t i = 0; i < size - 1; ++i) {
    object += vertices_[i].ToString();
    object += ", ";
  }
  object += vertices_[size - 1].ToString();
  object += ")";
  return object;
}

}  // namespace geometry

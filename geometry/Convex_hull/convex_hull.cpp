#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class Point {
 public:
  Point() = default;
  Point(int64_t x, int64_t y) : x(x), y(y) {
  }

  friend std::istream& operator>>(std::istream& in, Point& point) {
    int64_t x = 0;
    int64_t y = 0;
    in >> x >> y;
    point = Point(x, y);
    return in;
  }

  friend std::ostream& operator<<(std::ostream& out, const Point& point) {
    out << (point.x) << " " << (point.y) << "\n";
    return out;
  }

 public:
  int64_t x;
  int64_t y;
};

class Vector {
 public:
  Vector() = default;

  Vector(const Point& point1, const Point& point2) : x(point2.x - point1.x), y(point2.y - point1.y) {
  }

  Vector(int64_t x, int64_t y) : x(x), y(y) {
  }

  friend std::ostream& operator<<(std::ostream& out, const Vector& vector) {
    out << (vector.x) << " " << (vector.y) << "\n";
    return out;
  }

  double Length() const {
    return (sqrt(x * x + y * y));
  }

 public:
  int64_t x;
  int64_t y;
};

int64_t Abs(int64_t value) {
  if (value >= 0) {
    return value;
  }
  return -value;
}

int64_t VectorProduct(const Vector& vector1, const Vector& vector2) {
  return vector1.x * vector2.y - vector1.y * vector2.x;
}

class Polygon {
 public:
  friend std::istream& operator>>(std::istream& in, Polygon& polygon) {
    int n = 0;
    Point a;
    in >> n;
    for (int i = 0; i < n; ++i) {
      in >> a;
      polygon.vertices.push_back(a);
    }
    return in;
  }

  friend std::ostream& operator<<(std::ostream& out, const Polygon& polygon) {
    out << polygon.vertices.size() << "\n";
    out << polygon.vertices[0];
    for (size_t i = polygon.vertices.size() - 1; i >= 1; --i) {
      out << polygon.vertices[i];
    }
    return out;
  }

  int64_t PolygonAreaX2() const {
    int64_t square = 0;
    size_t size = vertices.size();
    Point o(0, 0);
    for (size_t i = 0; i < size; ++i) {
      Vector a(o, vertices[i % size]);
      Vector b(o, vertices[(i + 1) % size]);
      square += VectorProduct(a, b);
    }
    return (Abs(square));
  }

 public:
  std::vector<Point> vertices;
};

bool Comporator(const Point& a, const Point& b) {
  Point o(0, 0);
  Vector oa(o, a);
  Vector ob(o, b);
  return (VectorProduct(oa, ob) > 0 || (VectorProduct(oa, ob) == 0 && oa.Length() < ob.Length()));
}

bool Comporator2(const Point& a, const Point& b) {
  return (a.x < b.x || (a.x == b.x && a.y < b.y));
}

Polygon ConvexHull(std::vector<Point> points) {
  Polygon convex;
  Point startpoint = points[0];
  for (size_t i = 0; i < points.size(); ++i) {
    if (Comporator2(points[i], startpoint)) {
      startpoint = points[i];
    }
  }
  size_t size = points.size();
  for (size_t i = 0; i < size; ++i) {
    points[i].x -= startpoint.x;
    points[i].y -= startpoint.y;
  }
  std::sort(points.begin(), points.end(), Comporator);
  for (const auto& point : points) {
    while (convex.vertices.size() >= 2) {
      Vector a(convex.vertices[convex.vertices.size() - 1], point);
      Vector b(convex.vertices[convex.vertices.size() - 2], convex.vertices[convex.vertices.size() - 1]);
      if (VectorProduct(a, b) < 0) {
        break;
      }
      convex.vertices.pop_back();
    }
    convex.vertices.push_back(point);
  }
  for (size_t i = 0; i < convex.vertices.size(); ++i) {
    convex.vertices[i].x += startpoint.x;
    convex.vertices[i].y += startpoint.y;
  }
  return convex;
}

int main() {
  std::vector<Point> points;
  int n;
  std::cin >> n;
  Point a;
  for (int i = 0; i < n; ++i) {
    std::cin >> a;
    points.push_back(a);
  }
  Polygon convex(ConvexHull(points));
  std::cout << convex;
  int64_t square = convex.PolygonAreaX2();
  if (square % 2 == 0) {
    std::cout << (square / 2) << ".0\n";
  } else {
    std::cout << (square / 2) << ".5\n";
  }
}

#pragma once

#include <vector>

struct Point {
  double _x;
  double _y;
};

struct Color {
  double _r;
  double _g;
  double _b;
};

struct Path {
  double _thickness;
  Color _color;
  std::vector<Point> _points;
};

class Paint {
  private:
    Path _currentPath;
    std::vector<Path> _pathes;

  public:
    Paint();
    Paint(const Paint &) = delete;

    double getTickness() const;
    void setThickness(double t);

    const Color & getColor() const;
    void setColor(const Color & c);

    const Path & getCurrentPath() const;
    const std::vector<Path> & getPathes() const;

    void removeLast();
    void removeAll();

    void stepPath(const Point & p);
    void endPath();
};


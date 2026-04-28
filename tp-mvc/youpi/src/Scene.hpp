#pragma once

#include "Renderer.hpp"

#include <memory>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// shapes
///////////////////////////////////////////////////////////////////////////////

class Shape {
  public:
    virtual ~Shape() = default;
    virtual void render(Renderer & r) = 0;
};

class Line : public Shape {
  private:
    double _x0, _y0, _x1, _y1;
  public:
    Line(double x0, double y0, double x1, double y1);
    void render(Renderer & r) override;
};

class Circle : public Shape {
  private:
    double _x, _y, _r;
  public:
    Circle(double x, double y, double r);
    void render(Renderer & r) override;
};

///////////////////////////////////////////////////////////////////////////////
// scene
///////////////////////////////////////////////////////////////////////////////

class Scene {
  private:
    double _w, _h;
    std::vector<std::unique_ptr<Shape>> _shapes;

  public:
    Scene(double w, double h);
    void addLine(double x0, double y0, double x1, double y1);
    void addCircle(double x, double y, double r);
    void render(Renderer & r) const;
};

Scene mkHumanScene();

Scene mkFaceScene();


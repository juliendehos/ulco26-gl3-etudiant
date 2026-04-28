
#include "Scene.hpp"

///////////////////////////////////////////////////////////////////////////////
// Line
///////////////////////////////////////////////////////////////////////////////

Line::Line(double x0, double y0, double x1, double y1) :
  _x0(x0),
  _y0(y0),
  _x1(x1),
  _y1(y1)
{
}

void Line::render(Renderer & r) {
  r.renderLine(_x0, _y0, _x1, _y1);
}

Circle::Circle(double x, double y, double r) :
  _x(x),
  _y(y),
  _r(r)
{
}

///////////////////////////////////////////////////////////////////////////////
// Circle
///////////////////////////////////////////////////////////////////////////////

void Circle::render(Renderer & r) {
  r.renderCircle(_x, _y, _r);
}

Scene::Scene(double w, double h) :
  _w(w),
  _h(h)
{
}

///////////////////////////////////////////////////////////////////////////////
// Scene
///////////////////////////////////////////////////////////////////////////////

void Scene::addLine(double x0, double y0, double x1, double y1) {
  _shapes.push_back(std::make_unique<Line>(x0, y0, x1, y1));
}

void Scene::addCircle(double x, double y, double r) {
  _shapes.push_back(std::make_unique<Circle>(x, y, r));
}

void Scene::render(Renderer & r) const {
  r.renderSceneBegin(_w, _h);
  for (const auto & s : _shapes)
    s->render(r);
  r.renderSceneEnd();
}

Scene mkHumanScene() {
  Scene s(300, 400);
  s.addCircle(150, 100, 50);
  s.addLine(150, 150, 150, 280);
  s.addLine(150, 280, 100, 350);
  s.addLine(150, 280, 200, 350);
  s.addLine(150, 200, 100, 180);
  s.addLine(150, 200, 200, 180);
  return s;
}

Scene mkFaceScene() {
  Scene s(400, 400);
  s.addCircle(200, 200, 150);
  s.addCircle(150, 170, 20);
  s.addCircle(250, 170, 20);
  s.addLine(150, 270, 250, 270);
  s.addLine(150, 270, 130, 260);
  s.addLine(270, 260, 250, 270);
  return s;
}


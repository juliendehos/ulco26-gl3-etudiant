
#include "Paint.hpp"

#include "Params.hpp"

Paint::Paint():
  _currentPath({gDefaultTickness, gDefaultColor, {}})
{}

double Paint::getTickness() const {
  return _currentPath._thickness;
}

void Paint::setThickness(double t) {
  _currentPath._thickness = t;
}

const Color & Paint::getColor() const {
  return _currentPath._color;
}

void Paint::setColor(const Color & c) {
  _currentPath._color = c;
}

const Path & Paint::getCurrentPath() const {
  return _currentPath;
}

const std::vector<Path> & Paint::getPathes() const {
  return _pathes;
}

void Paint::stepPath(const Point & p) {
  _currentPath._points.push_back(p);
}

void Paint::endPath() {
  if (not _currentPath._points.empty()) {
    _pathes.push_back(_currentPath);
    _currentPath._points.clear();
  }
}

void Paint::removeLast() {
  if (not _pathes.empty())
    _pathes.pop_back();
}

void Paint::removeAll() {
  _pathes.clear();
}



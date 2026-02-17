#pragma once

#include <gtkmm.h>

#include "Paint.hpp"

///////////////////////////////////////////////////////////////////////////////
// MyDrawingArea
///////////////////////////////////////////////////////////////////////////////

class MyDrawingArea : public Gtk::DrawingArea {
  private:
    Paint & _paint;
    bool _isPainting;

  public:
    explicit MyDrawingArea(Paint & paint);

  protected:
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
    void on_mouse_pressed(int n_press, double x, double y);
    // TODO

  private:
    void drawPath(const Cairo::RefPtr<Cairo::Context>& cr, const Path & p);
    void drawPoint(const Cairo::RefPtr<Cairo::Context>& cr, const Point & p, double thickness);
};

///////////////////////////////////////////////////////////////////////////////
// MyWindow
///////////////////////////////////////////////////////////////////////////////

class MyWindow : public Gtk::Window {
  private:
    Paint _paint;
    MyDrawingArea _drawingArea;
    // TODO

  public:
    MyWindow();
};


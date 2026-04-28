#include "RendererCairo.hpp"

RendererCairo::RendererCairo(const Cairo::RefPtr<Cairo::Context>& cr, int w, int h) : 
  _cr(cr),
  _w(w),
  _h(h)
{
}

void RendererCairo::renderSceneBegin(double, double) {
  // background
  _cr->set_source_rgb(0.8, 0.8, 0.8);
  _cr->rectangle(0, 0, _w, _h);
  _cr->fill();
  // set brush
  _cr->set_source_rgb(0, 0, 0);
  _cr->set_line_width(2);
}

void RendererCairo::renderSceneEnd() {
}

void RendererCairo::renderLine(double x0, double y0, double x1, double y1) {
  _cr->move_to(x0, y0);
  _cr->line_to(x1, y1);
  _cr->stroke();
}

void RendererCairo::renderCircle(double x, double y, double r) {
  _cr->arc(x, y, r, 0.0, 2 * M_PI);
  _cr->stroke();
}


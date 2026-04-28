#pragma once

#include "Renderer.hpp"

#include <gtkmm.h>

class RendererCairo : public Renderer {
  private:
    const Cairo::RefPtr<Cairo::Context>& _cr;
    int _w, _h;

  public:
    RendererCairo(const Cairo::RefPtr<Cairo::Context>& cr, int w, int h);

    void renderSceneBegin(double w, double h) override;
    void renderSceneEnd() override;
    void renderLine(double x0, double y0, double x1, double y1) override;
    void renderCircle(double x, double y, double r) override;

};



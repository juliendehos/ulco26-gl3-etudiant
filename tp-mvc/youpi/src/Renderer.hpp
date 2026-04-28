#pragma once

class Renderer {
  public:
    virtual void renderSceneBegin(double w, double h) = 0;
    virtual void renderSceneEnd() = 0;
    virtual void renderLine(double x0, double y0, double x1, double y1) = 0;
    virtual void renderCircle(double x, double y, double r) = 0;
};


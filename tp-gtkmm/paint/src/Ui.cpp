
#include "Ui.hpp"

#include "Params.hpp"

#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// MyDrawingArea
///////////////////////////////////////////////////////////////////////////////

MyDrawingArea::MyDrawingArea(Paint & paint):
  _paint(paint),
  _isPainting(false)
{
  set_draw_func(sigc::mem_fun(*this, &MyDrawingArea::on_draw));

  auto mouse_click = Gtk::GestureClick::create();
  mouse_click->set_button(GDK_BUTTON_PRIMARY);
  mouse_click->signal_pressed().connect(sigc::mem_fun(*this, &MyDrawingArea::on_mouse_pressed));
  add_controller(mouse_click);
  
  // auto mouse_motion = Gtk::EventControllerMotion::create();
  // TODO

}

void MyDrawingArea::on_mouse_pressed(int n_press, double x, double y) {
  std::cout << "on_mouse_pressed (TODO)" << std::endl;
  queue_draw();
}

void MyDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {

  // background
  const auto [r, g, b] = gBgColor;
  cr->set_source_rgb(r, g, b);
  cr->rectangle(0, 0, width, height);
  cr->fill();

  // draw pathes
  for (const Path & p : _paint.getPathes())
    drawPath(cr, p);

  // draw current path
  drawPath(cr, _paint.getCurrentPath());
}

void MyDrawingArea::drawPoint(const Cairo::RefPtr<Cairo::Context>& cr, const Point & p, double thickness) {
  cr->arc(p._x, p._y, thickness*0.5, 0, 2.0 * M_PI);
  cr->fill();
}

void MyDrawingArea::drawPath(const Cairo::RefPtr<Cairo::Context>& cr, const Path & p) {

  // TODO

  cr->set_source_rgb(0, 0, 0);
  cr->set_line_width(20);
  cr->move_to(100, 100);
  cr->line_to(400, 200);
  cr->stroke();

  drawPoint(cr, {100, 100}, 20);

}

///////////////////////////////////////////////////////////////////////////////
// MyWindow
///////////////////////////////////////////////////////////////////////////////

MyWindow::MyWindow(): 
  _drawingArea(_paint)
{

  set_title(gTitle);
  set_default_size(gWindowWidth, gWindowHeight);

  // main hbox
  auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
  set_child(*hbox);

  // drawing area, on the left hand side
  hbox->append(_drawingArea);
  _drawingArea.set_hexpand(true);

  // tools panel, on the right hand side 
  auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
  vbox->set_size_request(gPanelWidth, -1);
  hbox->append(*vbox);

  // quit button
  auto quitButton = Gtk::make_managed<Gtk::Button>("Quit");
  vbox->append(*quitButton);
  quitButton->signal_clicked().connect([this](){ get_application()->quit(); });

  // thickness slider
  auto thicknessLabel = Gtk::make_managed<Gtk::Label>("Thickness:");
  thicknessLabel->set_margin_top(20);
  vbox->append(*thicknessLabel);

  auto thicknessScale = Gtk::make_managed<Gtk::Scale>();
  thicknessScale->set_range(1, gMaxTickness);
  thicknessScale->set_value(2);
  thicknessScale->set_draw_value(true);
  thicknessScale->set_increments(1, 5);
  thicknessScale->set_digits(0);
  vbox->append(*thicknessScale);
  // thicknessScale->signal_value_changed().connect(...);

  // TODO

}


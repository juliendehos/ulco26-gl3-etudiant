#include "UiGtkmm.hpp"

#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// MyDrawingArea
///////////////////////////////////////////////////////////////////////////////

MyDrawingArea::MyDrawingArea(MyWindow & window) :
  _window(window)
{
  set_content_width(gGameWidth);
  set_content_height(gGameHeight);
  set_draw_func(sigc::mem_fun(*this, &MyDrawingArea::on_draw));

  auto mouse_click = Gtk::GestureClick::create();
  mouse_click->set_button(GDK_BUTTON_PRIMARY);
  mouse_click->signal_released().connect(sigc::mem_fun(*this, &MyDrawingArea::on_mouse_released));
  add_controller(mouse_click);
}

void MyDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {

  // background
  {
    const Color & bgColor = _window.gameIsRunning() ? gBgColor : gBgEndColor;
    const auto [r, g, b] = bgColor;
    cr->set_source_rgb(r, g, b);
    cr->rectangle(0, 0, width, height);
    cr->fill();
  }

  // cells
  for (int i=0; i<N_ROWS; i++) {
    for (int j=0; j<N_COLS; j++) {
      // color
      const Cell cell = _window.gameCell(i, j);
      if (cell == Cell::Empty)
        continue;
      const auto [r, g, b] = cell == Cell::Player1 ? gPlayer1Color : gPlayer2Color;
      cr->set_source_rgb(r, g, b);

      // draw disk
      double x = j*gCellSize + gCellSize05;
      double y = (N_ROWS-1-i)*gCellSize + gCellSize05;
      cr->arc(x, y, gCellSize05, 0.0, 2.0 * M_PI);
      cr->fill();
    }
  }

  // grid
  cr->set_source_rgb(0, 0, 0);
  cr->set_line_width(2.0);
  // horizontal lines
  for (int i=1; i<N_ROWS; i++) {
    cr->move_to(0, i*gCellSize);
    cr->line_to(gGameWidth, i*gCellSize);
    cr->stroke();
  }
  // vertical lines
  for (int j=1; j<N_COLS; j++) {
    cr->move_to(j*gCellSize, 0);
    cr->line_to(j*gCellSize, gGameHeight);
    cr->stroke();
  }

}

void MyDrawingArea::on_mouse_released(int n_press, double x, double y) {
  const int j = x/gCellSize;
  _window.updateMove(j);
}

///////////////////////////////////////////////////////////////////////////////
// MyWindow
///////////////////////////////////////////////////////////////////////////////

static std::string fmtStatus(const Status s) {
  switch (s) {
    case Status::Play1: return "Red plays";
    case Status::Play2: return "Blue plays";
    case Status::Win1:  return "Red wins";
    case Status::Win2:  return "Blue wins";
    case Status::Tie:   return "It's a tie";
  }
  return {};
}

MyWindow::MyWindow() :
  _drawingArea(*this)
{

  // configure window
  set_title(gTitle);

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

  // "quit" button
  auto quitButton = Gtk::make_managed<Gtk::Button>("Quit");
  vbox->append(*quitButton);
  quitButton->signal_clicked().connect([this](){ get_application()->quit(); });

  // get player names from factory
  std::vector<Glib::ustring> playerStrings {"TODO human", "TODO random", "TODO mc10", "TODO mc100"};

  // player 2
  auto player2Label = Gtk::make_managed<Gtk::Label>("Blue player:");
  player2Label->set_margin_top(20);
  vbox->append(*player2Label);
  vbox->append(_player2Drop);
  _player2List = Gtk::StringList::create(playerStrings);
  _player2Drop.set_model(_player2List);
  _player2Drop.property_selected().signal_changed().connect(
    sigc::mem_fun(*this, &MyWindow::selectPlayer2));
  _player2Drop.set_selected(0);
  selectPlayer2();

  // status label
  _statusLabel.set_margin_top(20);
  vbox->append(_statusLabel);
  updateStatusLabel();
}

void MyWindow::updateMove(int move) {
  _game.playMove(move);
  updateStatusLabel();
  _drawingArea.queue_draw();
}

Cell MyWindow::gameCell(int i, int j) const {
  return _game.cell(i, j);
}

bool MyWindow::gameIsRunning() const {
  return _game.isRunning();
}

void MyWindow::updateStatusLabel() {
  const auto status = _game.status();
  const auto text = fmtStatus(status);
  _statusLabel.set_text(text);
}

void MyWindow::selectPlayer2() {
  const auto selected = _player2Drop.get_selected();
  const std::string selectedString = _player2List->get_string(selected);
  std::cout << "selected: " << selectedString << std::endl;
}


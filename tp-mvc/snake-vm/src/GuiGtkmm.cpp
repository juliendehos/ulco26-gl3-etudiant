
#include "GuiGtkmm.hpp"

#include "Params.hpp"
#include "Randomizer.hpp"

#include <thread>

///////////////////////////////////////////////////////////////////////////////
// MyDrawingArea
///////////////////////////////////////////////////////////////////////////////

MyDrawingArea::MyDrawingArea(const Game & game, const std::string & dataDir): 
  _game(game),
  _appleImage(Gdk::Pixbuf::create_from_file(dataDir + "apple-32.png"))
{
  set_content_width(gGameWidth);
  set_content_height(gGameHeight);
  set_draw_func(sigc::mem_fun(*this, &MyDrawingArea::on_draw));
}

void MyDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {

  // background
  cr->set_source_rgb(0.4, 0.4, 0.4);
  cr->rectangle(0, 0, width, height);
  cr->fill();

  // apple
  Vec applePos = vecToXY(_game.getApplePosition());
  Gdk::Cairo::set_source_pixbuf(cr, _appleImage, applePos._x, applePos._y);
  cr->paint();

  // snake
  const Snake & snake = _game.getSnake();

  // snake head
  Vec headPos = vecToXY(snake.getHead());
  cr->set_source_rgb(1.0, 1.0, 0.0);
  cr->rectangle(headPos._x, headPos._y, gCellSize, gCellSize);
  cr->fill();

  // snake body
  for ( const Vec & v : snake.getBody()) {
    Vec bodyPos = vecToXY(v);
    cr->set_source_rgb(1.0, 1.0, 1.0);
    cr->rectangle(bodyPos._x, bodyPos._y, gCellSize, gCellSize);
    cr->fill();
  }

}

Vec MyDrawingArea::vecToXY(const Vec & v) {
  return {v._x * gCellSize, v._y * gCellSize};
}

///////////////////////////////////////////////////////////////////////////////
// MyWindow
///////////////////////////////////////////////////////////////////////////////

MyWindow::MyWindow(Game & game, const std::string & dataDir) :
  _game(game),
  _myDrawingArea(game, dataDir),
  _scoreLabel()
{
    set_title(gAppName);

    auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
    set_child(*hbox);

    // drawing area
    hbox->append(_myDrawingArea);

    // left panel
    auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 10);
    vbox->set_size_request(150, -1);
    hbox->append(*vbox);

    auto quitButton = Gtk::make_managed<Gtk::Button>("Quit");
    vbox->append(*quitButton);

    updateScore(game.getScore());
    vbox->append(_scoreLabel);

    quitButton->signal_clicked().connect([this](){ get_application()->quit(); });

    // keyboard events
    auto controllerKey = Gtk::EventControllerKey::create();
    controllerKey->signal_key_pressed().connect(sigc::mem_fun(*this, &MyWindow::on_key_pressed), false);
    add_controller(controllerKey);

    // animation
    sigc::slot<bool()> mySlot = sigc::mem_fun(*this, &MyWindow::on_timeout);
    const int dt = gTimeStep*1000;
    Glib::signal_timeout().connect(mySlot, dt);

  }

bool MyWindow::on_timeout() {
  update(gTimeStep);
  return true;
}

bool MyWindow::on_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state) {
  switch (keyval) {
    case GDK_KEY_Left:
      _game.changeDirection(Direction::Left);
      return true;
    case GDK_KEY_Right:
      _game.changeDirection(Direction::Right);
      return true;
    case GDK_KEY_Up:
      _game.changeDirection(Direction::Up);
      return true;
    case GDK_KEY_Down:
      _game.changeDirection(Direction::Down);
      return true;
    case GDK_KEY_Escape:
      get_application()->quit();
      return true;
    default:
      return false;
  }
}

void MyWindow::updateScore(int score) {
  std::string txt = "score: " + std::to_string(score);
  _scoreLabel.set_text(txt);
}

void MyWindow::draw() {
  _myDrawingArea.queue_draw();
}

void MyWindow::update(const float dt) {
  const bool crash = _game.update(dt);
  updateScore(_game.getScore());
  if (crash) {
    _game.reset();
  }
  draw();
}

///////////////////////////////////////////////////////////////////////////////
// GuiGtkmm
///////////////////////////////////////////////////////////////////////////////

GuiGtkmm::GuiGtkmm(Game & game, const std::string & dataDir) :
  _game(game),
  _dataDir(dataDir)
{
}

void GuiGtkmm::run() {

  auto app = Gtk::Application::create();
  _pMyWindow = std::make_unique<MyWindow>(_game, _dataDir);
  app->signal_activate().connect([this, app] () {
    app->add_window(*_pMyWindow);
    _pMyWindow->set_visible(true);
  });
  app->run();

}


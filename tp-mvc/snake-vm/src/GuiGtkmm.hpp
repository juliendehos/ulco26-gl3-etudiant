#pragma once

#include "Game.hpp"

#include <gtkmm.h>

///////////////////////////////////////////////////////////////////////////////
// MyDrawingArea
///////////////////////////////////////////////////////////////////////////////

class MyDrawingArea : public Gtk::DrawingArea {
  private:
    const Game & _game;
    Glib::RefPtr<Gdk::Pixbuf> _appleImage;

  public:
    MyDrawingArea(const Game & game, const std::string & dataDir);

  private:
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
    Vec vecToXY(const Vec & v);
};

///////////////////////////////////////////////////////////////////////////////
// MyWindow
///////////////////////////////////////////////////////////////////////////////

class MyWindow : public Gtk::Window {
  private:
    Game & _game;
    MyDrawingArea _myDrawingArea;
    Gtk::Label _scoreLabel;

  public:

    MyWindow(Game & game, const std::string & dataDir);

    bool on_timeout();
    bool on_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state);

    void updateScore(int score);
    void draw();

  private:

    // update game and view, using the given step time
    void update(const float dt);
};

///////////////////////////////////////////////////////////////////////////////
// GuiGtkmm
///////////////////////////////////////////////////////////////////////////////

class GuiGtkmm {
  private:
    Game & _game;
    const std::string _dataDir;
    std::unique_ptr<MyWindow> _pMyWindow;

  public:
    GuiGtkmm(Game & game, const std::string & dataDir);
    void run();
};


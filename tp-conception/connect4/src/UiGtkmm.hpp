#pragma once

#include "Game.hpp"

#include <gtkmm.h>

#include <array>
#include <memory>

///////////////////////////////////////////////////////////////////////////////
// params
///////////////////////////////////////////////////////////////////////////////

using Color = std::array<double, 3>;

const std::string gTitle = "connect4";
const int gPanelWidth = 150;
const int gCellSize = 100;
const Color gBgColor{0.2, 0.6, 0.2};
const Color gBgEndColor{0.6, 0.6, 0.6};
const Color gPlayer1Color {1.0, 0.2, 0.2};
const Color gPlayer2Color {0.2, 0.2, 1.0};

const int gCellSize05 = gCellSize / 2;
const int gGameWidth = N_COLS*gCellSize;
const int gGameHeight = N_ROWS*gCellSize;

///////////////////////////////////////////////////////////////////////////////
// MyDrawingArea
///////////////////////////////////////////////////////////////////////////////

class MyWindow;

class MyDrawingArea : public Gtk::DrawingArea {
  private:
    MyWindow & _window;

  public:
    MyDrawingArea(MyWindow & window);

  protected:
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
    void on_mouse_released(int n_press, double x, double y);
};

///////////////////////////////////////////////////////////////////////////////
// MyWindow
///////////////////////////////////////////////////////////////////////////////

class MyWindow : public Gtk::Window {
  private:
    Game _game;

    MyDrawingArea _drawingArea;

    Gtk::DropDown _player2Drop;
    Glib::RefPtr<Gtk::StringList> _player2List;

    Gtk::Label _statusLabel;

  public:
    MyWindow();

    void updateMove(int move);
    Cell gameCell(int i, int j) const;
    bool gameIsRunning() const;

  private:
    void selectPlayer2();
    void updateStatusLabel();

};


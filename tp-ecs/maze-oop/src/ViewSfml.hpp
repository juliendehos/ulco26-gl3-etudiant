#pragma once

#include <SFML/Graphics.hpp>

#include "Game.hpp"

///////////////////////////////////////////////////////////////////////////////
// params
///////////////////////////////////////////////////////////////////////////////

const std::string gAppName = "maze-oop-sfml";

const sf::Vector2u gWinSize {1600, 800};
const int gHeaderHeight = 50;
const int gCellSize = 32;

const sf::Color gClearColor {187, 187, 187, 255};   // #bbb
const sf::Color gMazeColor {0, 0, 00, 255};
const sf::Color gWallColor {200, 40, 20, 255};

const sf::Color gTextColor = sf::Color::Black;

///////////////////////////////////////////////////////////////////////////////
// view
///////////////////////////////////////////////////////////////////////////////

class ViewSfml {

  private:

    const Game & _game;

    sf::RenderWindow _window;

    sf::Texture _bobTexture;
    sf::Sprite _bobSprite;

    sf::Texture _misoTexture;
    sf::Sprite _misoSprite;

    sf::RectangleShape _mazeRect;
    sf::RectangleShape _wallRect;

    sf::Font _arialFont;
    sf::Text _levelText;

  public:

    ViewSfml(const Game & game, const std::string & dataDir);
    ViewSfml(const ViewSfml & v) = delete;

    void draw();
    sf::RenderWindow & getWindow();

  private:
    const std::pair<float, float> ij2xy(const int i, const int j) const;

};



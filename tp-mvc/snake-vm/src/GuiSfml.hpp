#pragma once

#include "Game.hpp"

#include <SFML/Graphics.hpp>

class GuiSfml {

  private:
    Game & _game;

    sf::RenderWindow _window;

    sf::Texture _appleTexture;
    sf::Sprite _appleSprite;

    sf::RectangleShape _gameRect;
    sf::RectangleShape _headRect;
    sf::RectangleShape _bodyRect;

    sf::Font _arialFont;
    sf::Text _scoreText;

  public:
    GuiSfml(Game & game, const std::string & dataDir);

    void run();
    void draw();
    void updateScore(int score);

  private:
    sf::Vector2f vecToSf(const Vec & v) const;

    // update game and view, using the given step time
    void update(const float dt);
};


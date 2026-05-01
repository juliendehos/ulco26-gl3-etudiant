#pragma once

#include "Game.hpp"

#include <SFML/Graphics.hpp>

///////////////////////////////////////////////////////////////////////////////
// params
///////////////////////////////////////////////////////////////////////////////

const std::string gAppName = "asteroids-ecs-sfml";

const sf::Vector2f gWinSizeF {gGameWidth, gGameHeight};
const sf::Vector2u gWinSize(gWinSizeF);

const sf::Color gClearColor(0, 0, 0, 255);
const sf::Color gTextColor = sf::Color::Cyan;
const sf::Color gBulletColor = sf::Color::Yellow;

const sf::Vector2f gSpaceshipOrigin {25, 50};
const sf::Vector2f gAsteroidOrigin {50, 50};

const float gBulletRadius = 5;

///////////////////////////////////////////////////////////////////////////////
// view
///////////////////////////////////////////////////////////////////////////////

class ViewSfml {

  private:

    flecs::world & _ecs;

    sf::RenderWindow _window;

    sf::Font _arialFont;
    sf::Text _scoreText;

    sf::Texture _asteroidTexture;
    sf::Sprite _asteroidSprite;

    sf::Texture _spaceship1Texture;
    sf::Sprite _spaceship1Sprite;

    sf::Texture _spaceship2Texture;
    sf::Sprite _spaceship2Sprite;

    sf::CircleShape _bulletShape;

  public:

    ViewSfml(flecs::world & ecs, const std::string & dataDir);
    ViewSfml(const ViewSfml & v) = delete;

    void draw();
    sf::RenderWindow & getWindow();

};


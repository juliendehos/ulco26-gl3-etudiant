#pragma once

#include <SFML/Graphics.hpp>

#include <list>
#include <random>

///////////////////////////////////////////////////////////////////////////////
// apple
///////////////////////////////////////////////////////////////////////////////

class Apple {
  private:
    sf::Texture _texture;
    sf::Sprite _sprite;

  public:
    explicit Apple(const std::string & appleFilename);
    const sf::Sprite & getSprite() const;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f & p);
};

///////////////////////////////////////////////////////////////////////////////
// direction
///////////////////////////////////////////////////////////////////////////////

enum class Direction { Up, Down, Left, Right };

sf::Vector2f getMove(Direction direction);

///////////////////////////////////////////////////////////////////////////////
// snake
///////////////////////////////////////////////////////////////////////////////

class Snake {
  private:
    sf::RectangleShape _head;
    std::list<sf::RectangleShape> _body;
    Direction _direction;

  public:
    explicit Snake(float cellSize);
    sf::Vector2f getHeadPosition() const;
    void changeDirection(Direction direction);
    const sf::RectangleShape & getHead() const;
    const std::list<sf::RectangleShape> & getBody() const;

    // returns true if the snake eats the apple
    bool move(const Apple & apple, int cellSize);

    // returns true if the snake hits a border or itself
    bool collide(int nbWidth, int nbHeight, int cellSize) const;

    // returns true if the point is inside the body of the snake
    bool inBody (const sf::Vector2f & p) const;
};

///////////////////////////////////////////////////////////////////////////////
// game 
///////////////////////////////////////////////////////////////////////////////

class Game {
    // TODO
};


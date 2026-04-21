#pragma once

#include <SFML/Graphics.hpp>

#include <list>
#include <random>
#include <tuple>

///////////////////////////////////////////////////////////////////////////////
// Vec
///////////////////////////////////////////////////////////////////////////////

struct Vec {
  int _x;
  int _y;
};

void operator+=(Vec & v1, const Vec & v2);

bool operator==(const Vec & v1, const Vec & v2);

bool operator!=(const Vec & v1, const Vec & v2);

///////////////////////////////////////////////////////////////////////////////
// apple shape
///////////////////////////////////////////////////////////////////////////////

class AppleShape {
  private:
    sf::Texture _texture;
    sf::Sprite _sprite;

  public:
    explicit AppleShape(const std::string & appleFilename);
    const sf::Sprite & getSprite() const;
};

///////////////////////////////////////////////////////////////////////////////
// direction
///////////////////////////////////////////////////////////////////////////////

enum class Direction { Up, Down, Left, Right };

Vec getMove(Direction direction);

///////////////////////////////////////////////////////////////////////////////
// snake
///////////////////////////////////////////////////////////////////////////////

class Snake {
  private:
    Vec _head;
    std::list<Vec> _body;
    Direction _direction;

  public:
    explicit Snake(float cellSize);

    Vec getHead() const;
    const std::list<Vec> & getBody() const;
    void changeDirection(Direction direction);

    // returns true if the snake eats the apple
    bool move(const Vec & applePosition);

    // returns true if the snake hits a border or itself
    bool collide(int nbWidth, int nbHeight) const;

    // returns true if the point is inside the body of the snake
    bool inBody (const Vec & p) const;
};

///////////////////////////////////////////////////////////////////////////////
// game 
///////////////////////////////////////////////////////////////////////////////

class Game {
  private:
    const int _nbWidth;
    const int _nbHeight;
    const int _cellSize;
    const double _timeStep;

    int _score;
    double _time;
    std::default_random_engine _rng;

    Snake _snake;
    Vec _applePosition;

    AppleShape _appleShape;

    sf::RectangleShape _headRect;
    sf::RectangleShape _bodyRect;

  public:
    explicit Game(const std::string & appleFilename, int nbWidth, int nbHeight, int cellSize, double timeStep);
    void reset();

    int getScore() const;

    void changeDirection(Direction direction);
    void draw(sf::RenderWindow & window);

    std::tuple<bool, bool> update(double elapsed);
    // returns 2 booleans:
    // - the snake eats an apple
    // - the snake bumps into a wall

  private:
    void resetApple();
};


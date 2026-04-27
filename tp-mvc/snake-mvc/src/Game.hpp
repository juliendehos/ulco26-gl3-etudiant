#pragma once

#include <list>
#include <random>

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
    Snake();

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
    const double _timeStep;

    int _score;
    double _time;
    std::default_random_engine _rng;

    Snake _snake;
    Vec _applePosition;

  public:
    Game(int nbWidth, int nbHeight, double timeStep);
    void reset();

    int getScore() const;
    const Vec & getApplePosition() const;
    const Snake & getSnake() const;

    void changeDirection(Direction direction);

    // returns true if game over
    bool update(double elapsed);

  private:
    void resetApple();
};


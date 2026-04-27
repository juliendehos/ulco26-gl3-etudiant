
#include "Game.hpp"

#include <algorithm>

///////////////////////////////////////////////////////////////////////////////
// Vec
///////////////////////////////////////////////////////////////////////////////

void operator+=(Vec & v1, const Vec & v2) {
  v1._x += v2._x;
  v1._y += v2._y;
}

bool operator==(const Vec & v1, const Vec & v2) {
  return v1._x == v2._x and v1._y == v2._y;
}

bool operator!=(const Vec & v1, const Vec & v2) {
  return v1._x != v2._x or v1._y != v2._y;
}

///////////////////////////////////////////////////////////////////////////////
// direction
///////////////////////////////////////////////////////////////////////////////

Vec getMove(Direction direction) {
  switch (direction) {
    case Direction::Up:     return { 0, -1};
    case Direction::Down:   return { 0,  1};
    case Direction::Left:   return {-1,  0};
    case Direction::Right:  return { 1,  0};
  }
  return {};
}

///////////////////////////////////////////////////////////////////////////////
// snake
///////////////////////////////////////////////////////////////////////////////

Snake::Snake() :
  _head {1, 0},
  _body {{0, 0}},
  _direction(Direction::Right)
{
}

Vec Snake::getHead() const {
  return _head;
}

const std::list<Vec> & Snake::getBody() const {
  return _body;
}

bool Snake::inBody (const Vec & p) const {
  auto it = std::find(_body.begin(), _body.end(), p);
  return it != _body.end();
}

void Snake::changeDirection(Direction direction) {

  // skip opposite direction
  if ((_direction == Direction::Up and direction == Direction::Down) or
      (_direction == Direction::Down and direction == Direction::Up) or
      (_direction == Direction::Left and direction == Direction::Right) or
      (_direction == Direction::Right and direction == Direction::Left))
    return;

  _direction = direction;
}

bool Snake::move(const Vec & applePosition) {

  // move head
  Vec oldHead = _head;
  _head += getMove(_direction);

  // move body
  _body.push_front(oldHead);

  // check if the snake eats the apple
  if (_head == applePosition) {
    return true;
  }
  else {
    _body.pop_back();
    return false;
  }

}

bool Snake::collide(int nbWidth, int nbHeight) const {
  return 
    _head._x < 0 or _head._x > (nbWidth-1) or
    _head._y < 0 or _head._y > (nbHeight-1) or
    inBody(_head);
}

///////////////////////////////////////////////////////////////////////////////
// game 
///////////////////////////////////////////////////////////////////////////////

Game::Game(int nbWidth, int nbHeight, double timeStep):
  _nbWidth(nbWidth),
  _nbHeight(nbHeight),
  _timeStep(timeStep),
  _rng(std::default_random_engine(std::random_device{}()))
{
  reset();
}

void Game::reset() {
  _score = 0;
  _time = 0;
  _snake = Snake();
  resetApple();
}

int Game::getScore() const {
  return _score;
}

const Vec & Game::getApplePosition() const {
  return _applePosition;
}

const Snake & Game::getSnake() const {
  return _snake;
}

bool Game::update(double elapsed) {

  _time += elapsed;

  if (_time > _timeStep) {

    _time -= _timeStep;

    bool eat = _snake.move(_applePosition);
    bool crash = _snake.collide(_nbWidth, _nbHeight);

    if (eat) {
      resetApple();
      _score++;
    }

    return crash;
  }

  return false;
}

void Game::resetApple() {
  while (true) {
    std::uniform_int_distribution<int> distW(0, _nbWidth-1);
    std::uniform_int_distribution<int> distH(0, _nbHeight-1);
    int x = distW(_rng);
    int y = distH(_rng);
    Vec p {x, y};
    if (p != _snake.getHead() and not _snake.inBody(p)) {
      _applePosition = p;
      break;
    }
  }
}

void Game::changeDirection(Direction direction) {
  _snake.changeDirection(direction);
}


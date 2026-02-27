
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

sf::Vector2f v2ToSf(const Vec & v) {
  return {float(v._x), float(v._y)};
}

///////////////////////////////////////////////////////////////////////////////
// apple
///////////////////////////////////////////////////////////////////////////////

AppleShape::AppleShape(const std::string & appleFilename) :
  _texture(sf::Texture(appleFilename)), 
  _sprite(sf::Sprite(_texture))
{}

const sf::Sprite & AppleShape::getSprite() const {
  return _sprite;
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

Snake::Snake(float cellSize) :
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

Game::Game(const std::string & appleFilename, int nbWidth, int nbHeight, int cellSize, double timeStep):
  _nbWidth(nbWidth),
  _nbHeight(nbHeight),
  _cellSize(cellSize),
  _timeStep(timeStep),
  _rng(std::default_random_engine(std::random_device{}())), 
  _snake(cellSize),
  _appleShape(appleFilename),
  _headRect({float(cellSize), float(cellSize)}),
  _bodyRect({float(cellSize), float(cellSize)})
{
  _headRect.setFillColor(sf::Color::Yellow);
  _bodyRect.setFillColor(sf::Color::White);

  reset();
}

void Game::reset() {
  _score = 0;
  _time = 0;
  _snake = Snake(_cellSize);
  resetApple();
}

int Game::getScore() const {
  return _score;
}

std::tuple<bool,bool> Game::update(double elapsed) {

  _time += elapsed;

  if (_time > _timeStep) {

    _time -= _timeStep;

    bool eat = _snake.move(_applePosition);
    bool crash = _snake.collide(_nbWidth, _nbHeight);

    if (eat) {
      resetApple();
      _score++;
    }

    return {eat, crash};
  }

  return {false, false};
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

void Game::draw(sf::RenderWindow & window) {

  // draw apple
  sf::Vector2f spritePos = float(_cellSize) * v2ToSf(_applePosition);
  auto appleSprite = _appleShape.getSprite();
  appleSprite.setPosition(spritePos);
  window.draw(appleSprite);

  // snake
  // draw head
  sf::Vector2f headPos = float(_cellSize) * v2ToSf(_snake.getHead());
  _headRect.setPosition(headPos);
  window.draw(_headRect);

  // draw body
  for (const Vec & v : _snake.getBody()) {
    sf::Vector2f bodyPos = float(_cellSize) * v2ToSf(v);
    _bodyRect.setPosition(bodyPos);
    window.draw(_bodyRect);
  }

}


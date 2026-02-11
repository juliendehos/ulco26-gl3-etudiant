
#include "Game.hpp"

#include <algorithm>

///////////////////////////////////////////////////////////////////////////////
// apple
///////////////////////////////////////////////////////////////////////////////

Apple::Apple(const std::string & appleFilename) :
  _texture(sf::Texture(appleFilename)), 
  _sprite(sf::Sprite(_texture))
{}

const sf::Sprite & Apple::getSprite() const {
  return _sprite;
}

sf::Vector2f Apple::getPosition() const {
  return _sprite.getPosition();
}

void Apple::setPosition(const sf::Vector2f & p) {
  _sprite.setPosition(p);
}

///////////////////////////////////////////////////////////////////////////////
// direction
///////////////////////////////////////////////////////////////////////////////

sf::Vector2f getMove(Direction direction) {
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
  _head({cellSize, cellSize}),
  _direction(Direction::Right) {

    // init head
    _head.setFillColor(sf::Color::Yellow);
    _head.move({cellSize, 0});

    // init body
    auto body1 = sf::RectangleShape({cellSize, cellSize});
    body1.setFillColor(sf::Color::White);
    _body.push_back(body1);
  }

bool Snake::inBody (const sf::Vector2f & p) const {
  auto fBody = [&p](const sf::RectangleShape & r) {
    return p == r.getPosition();
  };
  auto it = std::find_if(_body.begin(), _body.end(), fBody);
  return it != _body.end();
}

sf::Vector2f Snake::getHeadPosition() const {
  return _head.getPosition();
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

const sf::RectangleShape & Snake::getHead() const {
  return _head;
}

const std::list<sf::RectangleShape> & Snake::getBody() const {
  return _body;
}

bool Snake::move(const Apple & apple, int cellSize) {

  // move head
  sf::RectangleShape oldHead = _head;
  sf::Vector2f v = float(cellSize) * getMove(_direction);
  _head.move(v);

  // move body
  oldHead.setFillColor(sf::Color::White);
  _body.push_front(oldHead);

  // check if the snake eats the apple
  if (_head.getPosition() == apple.getPosition()) {
    return true;
  }
  else {
    _body.pop_back();
    return false;
  }

}

bool Snake::collide(int nbWidth, int nbHeight, int cellSize) const {
  sf::Vector2f headPos = _head.getPosition();
  return 
    headPos.x < 0 or headPos.x > (cellSize*(nbWidth-1)) or
    headPos.y < 0 or headPos.y > (cellSize*(nbHeight-1)) or
    inBody(headPos);
}

///////////////////////////////////////////////////////////////////////////////
// game 
///////////////////////////////////////////////////////////////////////////////

// TODO




#include "GuiSfml.hpp"

#include "Params.hpp"
#include "Randomizer.hpp"

#include <thread>

GuiSfml::GuiSfml(Game & game, const std::string & dataDir):
  _game(game),
  _window(sf::VideoMode({gGameWidth, gGameHeight + 50}), gAppName, sf::Style::Close),
  _appleTexture(sf::Texture(dataDir + "apple-32.png")), 
  _appleSprite(sf::Sprite(_appleTexture)),
  _gameRect({gGameWidth, gGameHeight}),
  _headRect({gCellSize, gCellSize}),
  _bodyRect({gCellSize, gCellSize}),
  _arialFont(dataDir + "arial.ttf"),
  _scoreText(_arialFont, "", 25)
{
  _window.setFramerateLimit(60);
  _window.setPosition({50, 50});

  _gameRect.setFillColor(sf::Color({80, 80, 80, 255}));
  _headRect.setFillColor(sf::Color::Yellow);
  _bodyRect.setFillColor(sf::Color::White);

  _scoreText.setFillColor(sf::Color::Black);
  _scoreText.setPosition({20, gGameHeight + 10});
}

void GuiSfml::draw() {

  // clear screen
  _window.clear(sf::Color::Cyan);

  // draw game area
  _window.draw(_gameRect);

  // apple
  sf::Vector2f spritePos = float(gCellSize) * vecToSf(_game.getApplePosition());
  _appleSprite.setPosition(spritePos);
  _window.draw(_appleSprite);

  // snake 
  const Snake & snake = _game.getSnake();

  // draw head
  sf::Vector2f headPos = float(gCellSize) * vecToSf(snake.getHead());
  _headRect.setPosition(headPos);
  _window.draw(_headRect);

  // draw body
  for (const Vec & v : snake.getBody()) {
    sf::Vector2f bodyPos = float(gCellSize) * vecToSf(v);
    _bodyRect.setPosition(bodyPos);
    _window.draw(_bodyRect);
  }

  // draw score
  _window.draw(_scoreText);

  // render
  _window.display();
}

sf::Vector2f GuiSfml::vecToSf(const Vec & v) const {
  return {float(v._x), float(v._y)};
}

void GuiSfml::updateScore(int score) {
  _scoreText.setString("Score: " + std::to_string(score));
}

void GuiSfml::run() {
 
  // main loop
  sf::Clock clock;
  while (_window.isOpen()) {

    // handle events
    while (const std::optional event = _window.pollEvent()) {
      // window closed
      if (event->is<sf::Event::Closed>()) {
        _window.close();
      }
      // key pressed
      else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        auto code = keyPressed->scancode;
        if (code == sf::Keyboard::Scancode::Escape or code == sf::Keyboard::Scancode::Q)
          _window.close();
        else if (code == sf::Keyboard::Scancode::Left)
          _game.changeDirection(Direction::Left);
        else if (code == sf::Keyboard::Scancode::Right)
          _game.changeDirection(Direction::Right);
        else if (code == sf::Keyboard::Scancode::Up)
          _game.changeDirection(Direction::Up);
        else if (code == sf::Keyboard::Scancode::Down)
          _game.changeDirection(Direction::Down);
      }
    }

    sf::Time elapsed = clock.restart();
    double dt = elapsed.asSeconds();
    update(dt);

  }

}

void GuiSfml::update(const float dt) {
  const bool crash = _game.update(dt);
  updateScore(_game.getScore());
  if (crash) {
    _game.reset();
  }
  draw();
}


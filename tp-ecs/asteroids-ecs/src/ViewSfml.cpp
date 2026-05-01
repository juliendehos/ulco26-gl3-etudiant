
#include "ViewSfml.hpp"

ViewSfml::ViewSfml(flecs::world & ecs, const std::string & dataDir) :

  _ecs(ecs),

  _window(sf::VideoMode(gWinSize), gAppName, sf::Style::Close),

  _arialFont(dataDir + "arial.ttf"),
  _scoreText(_arialFont, "", 25),

  _asteroidTexture(dataDir + "asteroid.png"),
  _asteroidSprite(_asteroidTexture),

  _spaceship1Texture(dataDir + "spaceship1.png"),
  _spaceship1Sprite(_spaceship1Texture),

  _spaceship2Texture(dataDir + "spaceship2.png"),
  _spaceship2Sprite(_spaceship2Texture),

  _bulletShape(gBulletRadius)

{

  _window.setFramerateLimit(60);
  _window.setPosition({50, 50});

  _scoreText.setFillColor(gTextColor);
  _scoreText.setPosition({20, 10});

  _asteroidSprite.setOrigin(gAsteroidOrigin);
  _spaceship1Sprite.setOrigin(gSpaceshipOrigin);
  _spaceship2Sprite.setOrigin(gSpaceshipOrigin);
  _bulletShape.setFillColor(gBulletColor);

}

void ViewSfml::draw() {

  // clear screen
  _window.clear(gClearColor);

  // TODO [Step2] asteroids

  // TODO [Step1] spaceship

  // TODO [Step4] bullets

  // TODO [Step6] score

  // render
  _window.display();
}

sf::RenderWindow & ViewSfml::getWindow() {
  return _window;
}


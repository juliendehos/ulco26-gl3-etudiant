
#include "Game.hpp"
#include "ViewSfml.hpp"

ViewSfml::ViewSfml(flecs::world & ecs, const std::string & dataDir) :
  _ecs(ecs),
  _window(sf::VideoMode(gWinSize), gAppName, sf::Style::Close),
  _bobTexture(dataDir + "bob.png"),
  _bobSprite(_bobTexture),
  _misoTexture(dataDir + "miso.png"),
  _misoSprite(_misoTexture),
  _wallRect({gCellSize, gCellSize}),
  _arialFont(dataDir + "arial.ttf"),
  _levelText(_arialFont, "", 25)

{

  _window.setFramerateLimit(60);
  _window.setPosition({50, 50});

  _mazeRect.setFillColor(gMazeColor);
  _mazeRect.setPosition({0, gHeaderHeight});

  _wallRect.setFillColor(gWallColor);

  _levelText.setFillColor(gTextColor);
  _levelText.setPosition({20, 10});

}

void ViewSfml::draw() {

  // clear screen
  _window.clear(gClearColor);

  // TODO draw maze background

  // TODO draw walls

  // TODO draw targets

  // TODO draw player

  // TODO draw level
  _levelText.setString("TODO");
  _window.draw(_levelText);

  // render
  _window.display();

}

sf::RenderWindow & ViewSfml::getWindow() {
  return _window;
}

const std::pair<float, float> ViewSfml::pos2xy(const Position & pos) const {
  const float x = pos.j * gCellSize;
  const float y = pos.i * gCellSize + gHeaderHeight;
  return {x, y};
}


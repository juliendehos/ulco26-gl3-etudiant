#include "ViewSfml.hpp"

ViewSfml::ViewSfml(const Game & game, const std::string & dataDir) :
  _game(game),
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

  const int ni = _game.getNi();
  const int nj = _game.getNj();

  // draw maze background
  const float w = gCellSize * nj;
  const float h = gCellSize * ni;
  _mazeRect.setSize({w, h});
  _window.draw(_mazeRect);

  // draw board
  for (int i=0; i<ni; i++) {
    for (int j=0; j<nj; j++) {

      auto [x, y] = ij2xy(i, j);
      const Cell cell = _game.cell(i, j);

      // walls
      if (cell == Cell::Wall) {
        _wallRect.setPosition({x, y});
        _window.draw(_wallRect);
      }

      // targets
      else if (cell == Cell::Target) {
        _misoSprite.setPosition({x, y});
        _window.draw(_misoSprite);
      }

    }
  }

  // draw player
  {
    const auto [i, j] = _game.getPlayer();
    const auto [x, y] = ij2xy(i, j);
    _bobSprite.setPosition({x, y});
    _window.draw(_bobSprite);
  }

  // draw level
  const int level = _game.getLevel();
  const std::string levelText = "level: " + std::to_string(level);
  _levelText.setString(levelText);
  _window.draw(_levelText);

  // render
  _window.display();

}

sf::RenderWindow & ViewSfml::getWindow() {
  return _window;
}

const std::pair<float, float> ViewSfml::ij2xy(const int i, const int j) const {
  const float x = j * gCellSize;
  const float y = i * gCellSize + gHeaderHeight;
  return {x, y};
}



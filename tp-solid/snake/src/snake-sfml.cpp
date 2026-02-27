
#include "Game.hpp" 

#include <SFML/Graphics.hpp>

#include <filesystem>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// global parameters
///////////////////////////////////////////////////////////////////////////////

const double gTimeStep = 0.15;
const int gNbWidth = 30;
const int gNbHeight = 20;
const int gCellSize = 32;     // fits "data/apple-32.png"
const int gWinWidth = gCellSize * gNbWidth;
const int gWinHeight = gCellSize * gNbHeight;

///////////////////////////////////////////////////////////////////////////////
// application
///////////////////////////////////////////////////////////////////////////////

int main(int, char ** argv) {

  // assets
  const std::string dataDir = 
    (std::filesystem::path(argv[0]).parent_path() / "../data/").string();
  const std::string appleFilename = dataDir + "apple-32.png";
  const sf::Color bgColor(80, 80, 80, 255);

  // window
  sf::RenderWindow window(sf::VideoMode({gWinWidth, gWinHeight}), "snake", sf::Style::Close);
  window.setFramerateLimit(60);
  window.setPosition({50, 50});

  // game data
  Game game(appleFilename, gNbWidth, gNbHeight, gCellSize, gTimeStep);
  sf::Clock clock;

  // main loop
  while (window.isOpen()) {

    // handle events
    while (const std::optional event = window.pollEvent()) {
      // window closed
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      // key pressed
      else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        auto code = keyPressed->scancode;
        if (code == sf::Keyboard::Scancode::Escape or code == sf::Keyboard::Scancode::Q)
          window.close();
        else if (code == sf::Keyboard::Scancode::Left)
          game.changeDirection(Direction::Left);
        else if (code == sf::Keyboard::Scancode::Right)
          game.changeDirection(Direction::Right);
        else if (code == sf::Keyboard::Scancode::Up)
          game.changeDirection(Direction::Up);
        else if (code == sf::Keyboard::Scancode::Down)
          game.changeDirection(Direction::Down);
      }
    }

    // handle time
    sf::Time elapsed = clock.restart();
    const auto [eat, crash] = game.update(elapsed.asSeconds());
    if (eat) {
      std::cout << "score: " << game.getScore() << std::endl;
    }
    if (crash) {
      game.reset();
      std::cout << "\nscore: " << game.getScore() << std::endl;
    }

    // refresh display
    window.clear(bgColor);
    game.draw(window);
    window.display();
  }

  return 0;
}


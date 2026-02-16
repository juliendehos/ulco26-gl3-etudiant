
#include "Game.hpp" 

#include <SFML/Graphics.hpp>

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
  const sf::Color bgColor(80, 80, 80, 255);

  // window
  sf::RenderWindow window(sf::VideoMode({gWinWidth, gWinHeight}), "snake", sf::Style::Close);
  window.setFramerateLimit(60);
  window.setPosition({50, 50});

  // create the clock
  sf::Clock clock;

  // create the game
  // TODO

  // main loop
  // TODO

    // handle events
    // TODO

    // update the game
    // TODO

    // refresh display
    // TODO


  // display the final score
  // TODO

  return 0;
}


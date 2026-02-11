
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
  window.setVerticalSyncEnabled(true);
  window.setPosition({50, 50});

  // create the clock
  sf::Clock clock;

  // exemple d'utilisation de clock (TODO à supprimer):
  sf::Time elapsed = clock.restart();
  double dt = elapsed.asSeconds();
  std::cout << "Elapsed time: " <<  dt << "s." << std::endl;

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


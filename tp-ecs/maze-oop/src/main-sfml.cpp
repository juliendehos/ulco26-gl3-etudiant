
#include "Game.hpp"
#include "ViewSfml.hpp"

#include <filesystem>

///////////////////////////////////////////////////////////////////////////////
// handleEvents
///////////////////////////////////////////////////////////////////////////////

void handleEvents(sf::RenderWindow & window, Game & game) {
  while (const std::optional event = window.pollEvent()) {

    // window closed
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    // keyboard
    else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      auto code = keyPressed->scancode;
      switch (code) {
        case sf::Keyboard::Scancode::Escape:  window.close(); break;
        case sf::Keyboard::Scancode::Q:       window.close(); break;
        case sf::Keyboard::Scancode::Up:      game.playMove(Move::Up); break;
        case sf::Keyboard::Scancode::Down:    game.playMove(Move::Down); break;
        case sf::Keyboard::Scancode::Left:    game.playMove(Move::Left); break;
        case sf::Keyboard::Scancode::Right:   game.playMove(Move::Right); break;
        default: break;
      }
    }

  }
}

///////////////////////////////////////////////////////////////////////////////
// main
///////////////////////////////////////////////////////////////////////////////

int main(int, char ** argv) {

  // assets
  const std::string dataDir = 
    (std::filesystem::path(argv[0]).parent_path() / "../data/").string();

  // game
  Game game(dataDir);

  // view
  ViewSfml view(game, dataDir);
  sf::RenderWindow & window = view.getWindow();

  // main loop
  while (window.isOpen()) {
    handleEvents(window, game);
    view.draw();
  }

  return 0;
}



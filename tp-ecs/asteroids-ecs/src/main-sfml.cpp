
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

    // key pressed
    else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      auto code = keyPressed->scancode;
      switch (code) {
      case sf::Keyboard::Scancode::Escape:  window.close(); break;
      case sf::Keyboard::Scancode::Q:       window.close(); break;
      case sf::Keyboard::Scancode::Left:    game.moveLeft(true); break;
      case sf::Keyboard::Scancode::Right:   game.moveRight(true); break;
      case sf::Keyboard::Scancode::Up:      game.moveForward(true); break;
      case sf::Keyboard::Scancode::Space:   game.moveFire(); break;
      }
    }

    // key released
    else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
      auto code = keyReleased->scancode;
      switch (code) {
      case sf::Keyboard::Scancode::Left:    game.moveLeft(false); break;
      case sf::Keyboard::Scancode::Right:   game.moveRight(false); break;
      case sf::Keyboard::Scancode::Up:      game.moveForward(false); break;
      case sf::Keyboard::Scancode::Space:   game.moveLoad(); break;
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

  // ecs
  flecs::world ecs;

  // game
  Game game(ecs);

  // view
  ViewSfml view(ecs, dataDir);
  sf::RenderWindow & window = view.getWindow();

  // systems

  ecs.system("events").run([&window, &game](flecs::iter &) {
      handleEvents(window, game);
  });

  ecs.system("update").run([&game](flecs::iter & it) {
    const double dt = it.delta_time();
    game.updateMoves(dt);
    game.updatePhysics(dt);
    game.updateData(dt);
  });

  ecs.system("draw").run([&window, &view](flecs::iter &) {
    view.draw();
  });

  // main loop
  while (window.isOpen()) {
    ecs.progress();
  }

  return 0;
}


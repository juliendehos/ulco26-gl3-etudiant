
#include "Randomizer.hpp"

#include "Game.hpp"

#include <chrono>
#include <thread>

Randomizer::Randomizer(Game & game, bool & isRunning, const float tMin, const float tMax) :
  _game(game),
  _isRunning(isRunning),
  _engine(std::random_device{}()),
  _dist(tMin, tMax)
{
}

void Randomizer::run() {
  while (_isRunning) {
    const int ms = 1000 * _dist(_engine);
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    _game.changeDirection(Direction::Down);
  }
}


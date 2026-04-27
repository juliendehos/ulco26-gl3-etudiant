#pragma once

#include "Game.hpp"

#include <random>

class Randomizer {
  private:
    Game & _game;
    bool & _isRunning;
    std::default_random_engine _engine;
    std::uniform_real_distribution<float> _dist;

  public:

    // Calls game.changeDirection(Direction::Down) randomly. 
    // - isRunning: reference to a boolean indicating if the game is still running.
    // - tMin/tMax: min/max random time to wait before calling changeDirection.
    Randomizer(Game & game, bool & isRunning, const float tMin, const float tMax);

    // Run the randomizer, while the game is running.
    void run();
};


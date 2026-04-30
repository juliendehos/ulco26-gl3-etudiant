#pragma once

#include <flecs.h>

#include <vector>
#include <string>

struct Position {
  int i, j;
};

bool operator==(const Position & p1, const Position & p2);

struct Wall {};
struct Target {};
struct Player {};

struct Level {
  unsigned value;
};

struct Maze {
  int ni, nj;
};

enum class Move {
  Up,
  Down,
  Left,
  Right
};

class Game {

  private:
    std::vector<std::string> _filenames;

    flecs::world & _ecs;
    flecs::entity _player;

  public:
    Game(flecs::world & ecs, const std::string & dataDir);
    Game(const Game &) = delete;
    void playMove(const Move move);

  private:
    void loadLevel();
};


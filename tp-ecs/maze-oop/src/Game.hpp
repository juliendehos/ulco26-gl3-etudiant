#pragma once

#include <string>
#include <vector>

enum class Move {
  Up,
  Down,
  Left,
  Right
};

enum class Cell {
  Empty,
  Wall,
  Target
};

struct Player {
  int i;
  int j;
};

class Game {

  private:
    std::vector<std::string> _filenames;

    int _level;

    std::vector<Cell> _board;
    int _ni;
    int _nj;

    Player _player;

  public:
    Game(const std::string & dataDir);
    void playMove(const Move move);

    Cell cell(int i, int j) const;
    int getNi() const;
    int getNj() const;
    const Player & getPlayer() const;
    int getLevel() const;

  private:
    void loadLevel();
    Cell & cell(int i, int j);
};



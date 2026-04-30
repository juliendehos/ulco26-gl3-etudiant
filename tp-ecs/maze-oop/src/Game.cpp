#include "Game.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

Game::Game(const std::string & dataDir) :
  _filenames ({
    dataDir + "maze1.txt",
    dataDir + "maze2.txt",
    dataDir + "maze3.txt",
    dataDir + "maze4.txt"
  }),
  _level(0)
{
  loadLevel();
}

Cell & Game::cell(int i, int j) {
  const int k = i*_nj + j;
  return _board[k];
}

Cell Game::cell(int i, int j) const {
  const int k = i*_nj + j;
  return _board[k];
}

int Game::getNi() const {
  return _ni;
}

int Game::getNj() const {
  return _nj;
}

const Player & Game::getPlayer() const {
  return _player;
}

int Game::getLevel() const {
  return _level;
}

void Game::loadLevel() {

  // get maze filename
  const std::string & filename = _filenames[_level];
  
  // load maze
  try {
    std::string line;
    std::ifstream ifs(filename);

    // read header (ni, nj, i0, j0)
    std::getline(ifs, line);
    std::istringstream issHeader(line);
    issHeader >> _ni >> _nj;

    _board = std::vector<Cell>(_ni*_nj, Cell::Empty);

    // read maze
    for (int i=0; i<_ni; i++) {
      std::getline(ifs, line);
      std::istringstream iss(line);

      for (int j=0; j<_nj; j++) {
        const char c = iss.get();
        if (c == '+') {
          cell(i, j) = Cell::Wall;
        }
        else if (c == '?') {
          cell(i, j) = Cell::Target;
        }
        else if (c == 'o') {
          _player = {i, j};
        }
      }
    }

  }
  catch(...) {
    std::cerr << "Cannot read " << filename << std::endl;
  }

}

void Game::playMove(const Move move) {

  auto [i, j] = _player;

  // move position pos
  switch (move) {
    case Move::Up:    i--;  break;
    case Move::Down:  i++;  break;
    case Move::Left:  j--;  break;
    case Move::Right: j++;  break;
  }

  // wrap maze
  if (i < 0)      i = _ni-1;
  if (i >= _ni)   i = 0;
  if (j < 0)      j = _nj-1;
  if (j >= _nj)   j = 0;

  // handle target
  if (cell(i, j) == Cell::Target) {
    _level = (_level + 1) % _filenames.size();
    loadLevel();
  }
  else {

    // handle wall
    if (cell(i, j) == Cell::Wall) {
      i = _player.i;
      j = _player.j;
    }

    // set new pos
    _player = {i, j};
  }
}


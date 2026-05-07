
#include "Game.hpp"

inline int ij2k(int i, int j) {
  return i*N_COLS + j;
}

Game::Game() : _firstStatus(Status::Play2) {
  newGame();
}

void Game::newGame() {

  // switch first player
  if (_firstStatus == Status::Play1) {
    _firstStatus = Status::Play2;
  }
  else {
    _firstStatus = Status::Play1;
  }

  // init game data
  _currentStatus = _firstStatus;
  _board.fill(Cell::Empty);
  _heights.fill(0);
  _nMoves = 0;
}

Status Game::getStatus() const {
  return _currentStatus;
}

Cell Game::getCell(int i, int j) const {
  return _board[ ij2k(i,j) ];
}

bool Game::isRunning() const {
  return _currentStatus == Status::Play1 or _currentStatus == Status::Play2;
}

bool Game::play(int j) {

  const int i = _heights[j];

  // check if the move is valid
  if (not isRunning() or j<0 or j>=N_COLS or i>=N_ROWS)
    return false;

  const Cell cell = 
    _currentStatus == Status::Play1 ? Cell::Player1 : Cell::Player2;

  // update game data
  _board[ ij2k(i,j) ] = cell;
  _heights[j] += 1;
  _nMoves += 1;

  // check win conditions and update the current status
  if (checkLine(cell, i, j, 1, 0) 
      or checkLine(cell, i, j, 0, 1)
      or checkLine(cell, i, j, 1, 1)
      or checkLine(cell, i, j, 1, -1)) {
    _currentStatus = cell == Cell::Player1 ? Status::Win1 : Status::Win2;
  }
  else if (_nMoves == N_ROWS*N_COLS) {
    _currentStatus = Status::Tie;
  }
  else {
    _currentStatus = 
      cell == Cell::Player1 ? Status::Play2 : Status::Play1;
  }

  return true;
}

bool Game::checkLine(Cell c, int i, int j, int di, int dj) const {
  const int n1 = countLine(c, i, j, di, dj);
  const int n2 = countLine(c, i, j, -di, -dj);
  return n1 + n2 + 1 >= N_WIN;
}

int Game::countLine(Cell c, int i, int j, int di, int dj) const {
  int in = i + di;
  int jn = j + dj;
  int n = 0;
  while (in>=0 and in<N_ROWS and jn>=0 and jn<N_COLS
      and _board[ij2k(in,jn)] == c) {
    n += 1;
    in += di;
    jn += dj;
  }
  return n;
}

std::vector<int> Game::computeValidMoves() const {
  std::vector<int> moves;
  for (int j=0; j<N_COLS; j++) {
    if (_heights[j] < N_ROWS)
      moves.push_back(j);
  }
  return moves;
}


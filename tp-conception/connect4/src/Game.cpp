
#include "Game.hpp"

///////////////////////////////////////////////////////////////////////////////
// Board
///////////////////////////////////////////////////////////////////////////////

Cell Board::cell(int i, int j) const {
  return _cells[i*N_COLS + j];
}

Cell & Board::cell_(int i, int j) {
  return _cells[i*N_COLS + j];
}

void Board::newBoard() {
  _cells.fill(Cell::Empty);
}

///////////////////////////////////////////////////////////////////////////////
// Game
///////////////////////////////////////////////////////////////////////////////


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
  _status = _firstStatus;
  _board.newBoard();
  _heights.fill(0);
  _nMoves = 0;
}

Status Game::status() const {
  return _status;
}

bool Game::isRunning() const {
  return _status == Status::Play1 or _status == Status::Play2;
}

Cell Game::cell(int i, int j) const {
  return _board.cell(i, j);
}

bool Game::playMove(int j) {

  const int i = _heights[j];

  // check if the move is valid
  if (not isRunning() or j<0 or j>=N_COLS or i>=N_ROWS)
    return false;

  const Cell cell = 
    _status == Status::Play1 ? Cell::Player1 : Cell::Player2;

  // update game data
  _board.cell_(i, j) = cell;
  _heights[j] += 1;
  _nMoves += 1;

  // check win conditions and update the current status
  if (checkLine(cell, i, j, 1, 0) 
      or checkLine(cell, i, j, 0, 1)
      or checkLine(cell, i, j, 1, 1)
      or checkLine(cell, i, j, 1, -1)) {
    _status = cell == Cell::Player1 ? Status::Win1 : Status::Win2;
  }
  else if (_nMoves == N_ROWS*N_COLS) {
    _status = Status::Tie;
  }
  else {
    _status = 
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
  while (in>=0 and in<N_ROWS and jn>=0 and jn<N_COLS and _board.cell(in,jn) == c) {
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


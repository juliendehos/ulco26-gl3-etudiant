
#include "Game.hpp"


///////////////////////////////////////////////////////////////////////////////
// global functions
///////////////////////////////////////////////////////////////////////////////

// find opponent cells to capture, starting from an empty position and going to a given direction
void computeValidMovesDiDj(const Board & board, Moves & moves, int i0, int j0, int di, int dj, Cell cOur, Cell cOpp) {
  std::set<Pos> capturedCells;
  int i = i0 + di;
  int j = j0 + dj;
  // capture opponent cells in the di/dj direction
  while (true) {
    // we're outside the board
    if (i<0 or i>=N_ROWS or j<0 or j>=N_COLS)
      break;
    const Cell c = board.cell(i, j);
    // we've found a new opponent cell to capture
    if (c == cOpp) {
      capturedCells.insert({i, j});
      i += di;
      j += dj;
    }
    else {
      // we've found one of our cells, so we can capture opponent cells, using the initial position
      if (c == cOur) {
        if (not capturedCells.empty())
          moves[{i0, j0}].merge(capturedCells);
        break;
      }
      // we've found an empty cell, so we can't capture opponent cells, using the initial position
      else 
        break;
    }
  }
}


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
  const int i2 = N_ROWS / 2;
  const int j2 = N_COLS / 2;
  cell_(i2, j2-1) = Cell::Player1;
  cell_(i2-1, j2) = Cell::Player1;
  cell_(i2, j2) = Cell::Player2;
  cell_(i2-1, j2-1) = Cell::Player2;
}


///////////////////////////////////////////////////////////////////////////////
// Game
///////////////////////////////////////////////////////////////////////////////



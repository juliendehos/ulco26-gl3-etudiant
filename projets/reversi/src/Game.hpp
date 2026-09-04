#pragma once

#include <array>
#include <map>
#include <set>

const int N_ROWS = 8;   // number of rows
const int N_COLS = 8;   // number of columns

enum class Status { Play1, Play2, Win1, Win2, Tie };

enum class Cell { Player1, Player2, Empty };

// position (i, j) in a board
using Pos = std::pair<int, int>;

// new position + captured positions
using Moves = std::map<Pos, std::set<Pos>>;

class Board {
  private:
    std::array<Cell, N_ROWS*N_COLS> _cells;

  public:
    Cell cell(int i, int j) const;
    Cell & cell_(int i, int j);
    void newBoard();
};

class Game {
  // TODO
};

// Check if the move starting from the empty position (i0, j0) and going to the direction (di, dj) is valid.
// If the move is valid, the function adds the starting position and the captured positions in moves.
void computeValidMovesDiDj(const Board & board, Moves & moves, int i0, int j0, int di, int dj, Cell cOur, Cell cOpp);


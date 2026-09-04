#pragma once

#include <array>
#include <vector>

const int N_ROWS = 6;   // number of rows
const int N_COLS = 7;   // number of columns
const int N_WIN = 4;    // number of cells to align

enum class Status { Play1, Play2, Win1, Win2, Tie };

enum class Cell { Player1, Player2, Empty };

class Board {
  private:
    std::array<Cell, N_ROWS*N_COLS> _cells;

  public:
    Cell cell(int i, int j) const;
    Cell & cell_(int i, int j);
    void newBoard();
};

class Game {

  private:

    Status _status;
    Status _firstStatus;
    Board _board;
    std::array<int, N_COLS> _heights;
    int _nMoves;

  public:

    Game();

    void newGame();

    // Returns the current game status.
    Status status() const;

    // Returns if the current game is running (i.e. Status::Play1 or Status::Play2).
    bool isRunning() const;

    // Returns the cell at the position (i, j). Assumes the position is valid.
    Cell cell(int i, int j) const;

    // Play a move. Returns true is the move j has been successfully played.
    bool playMove(int j);

    // Compute the valid moves of the current game. Useful for AI players.
    std::vector<int> computeValidMoves() const;

  private:

    bool checkLine(Cell c, int i, int j, int di, int dj) const;

    int countLine(Cell c, int i, int j, int di, int dj) const;

};


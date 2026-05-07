#pragma once

#include <array>
#include <vector>

const int N_ROWS = 6;   // number of rows
const int N_COLS = 7;   // number of columns
const int N_WIN = 4;    // number of cells to align

enum class Status { Play1, Play2, Win1, Win2, Tie };

enum class Cell { Player1, Player2, Empty };

class Game {

  private:

    Status _currentStatus;
    Status _firstStatus;
    std::array<Cell, N_ROWS*N_COLS> _board;
    std::array<int, N_COLS> _heights;
    int _nMoves;

  public:

    Game();

    void newGame();

    Status getStatus() const;

    // assumes the position (i, j) is valid
    Cell getCell(int i, int j) const;

    bool isRunning() const;

    // returns true is the move j has been played 
    bool play(int j);

    // for AI
    std::vector<int> computeValidMoves() const;

  private:

    bool checkLine(Cell c, int i, int j, int di, int dj) const;

    int countLine(Cell c, int i, int j, int di, int dj) const;

};


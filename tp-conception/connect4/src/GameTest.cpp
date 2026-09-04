
#include "Game.hpp"

#include <catch2/catch_test_macros.hpp>

///////////////////////////////////////////////////////////////////////////////
// helpers
///////////////////////////////////////////////////////////////////////////////

bool playMoves(Game & game, const std::vector<int> & js) {
  for (const int j : js) {
    const bool res = game.playMove(j);
    if (not res)
      return false;
  }
  return true;
}

///////////////////////////////////////////////////////////////////////////////
// test Game methods
///////////////////////////////////////////////////////////////////////////////

TEST_CASE ("newGame 1", "[Game]") {

  Game game;
  REQUIRE( game.status() == Status::Play1 );

  for (int i=0; i<N_ROWS; i++) {
    for (int j=0; j<N_COLS; j++) {
      REQUIRE( game.cell(i, j) == Cell::Empty );
    }
  }

}

TEST_CASE ("newGame 2", "[Game]") {

  Game game;
  game.newGame();
  REQUIRE( game.status() == Status::Play2 );

  for (int i=0; i<N_ROWS; i++) {
    for (int j=0; j<N_COLS; j++) {
      REQUIRE( game.cell(i, j) == Cell::Empty );
    }
  }

}

TEST_CASE ("playMove ok", "[Game]") {

  Game game;
  const bool res = game.playMove(1);
  REQUIRE( res == true );
  REQUIRE( game.status() == Status::Play2 );

  for (int i=0; i<N_ROWS; i++) {
    for (int j=0; j<N_COLS; j++) {
      if (i==0 and j==1) {
        REQUIRE( game.cell(0, 1) == Cell::Player1 );
      }
      else {
        REQUIRE( game.cell(i, j) == Cell::Empty );
      }
    }
  }

}

TEST_CASE ("playMove ko", "[Game]") {

  Game game;
  const bool res = game.playMove(42);
  REQUIRE( res == false );
  REQUIRE( game.status() == Status::Play1 );

  for (int i=0; i<N_ROWS; i++) {
    for (int j=0; j<N_COLS; j++) {
      REQUIRE( game.cell(i, j) == Cell::Empty );
    }
  }

}

TEST_CASE ("playMove win1, stop", "[Game]") {
  Game game;
  std::vector<int> js {
    1, 1,
    2, 2,
    3, 3,
    4
  };
  playMoves(game, js);
  const bool res = game.playMove(4);
  REQUIRE( res == false );
  REQUIRE( game.status() == Status::Win1 );
}

TEST_CASE ("playMove win2, stop", "[Game]") {
  Game game;
  game.newGame();
  std::vector<int> js {
    1, 1,
    2, 2,
    3, 3,
    4
  };
  playMoves(game, js);
  const bool res = game.playMove(4);
  REQUIRE( res == false );
  REQUIRE( game.status() == Status::Win2 );
}

TEST_CASE ("full column", "[Game]") {
  Game game;
  std::vector<int> js {
    1, 1,
    1, 1,
    1, 1,
  };
  const bool res1 = playMoves(game, js);
  REQUIRE( res1 == true );
  const bool res2 = game.playMove(1);
  REQUIRE( res2 == false );
  REQUIRE( game.status() == Status::Play1 );
}

///////////////////////////////////////////////////////////////////////////////
// test game scenarios
///////////////////////////////////////////////////////////////////////////////

TEST_CASE ("playMove win1 row", "[Game]") {
  Game game;
  std::vector<int> js {
    1, 1,
    2, 2,
    3, 3,
    4
  };
  const bool res = playMoves(game, js);
  REQUIRE( res == true );
  REQUIRE( game.status() == Status::Win1 );
}

TEST_CASE ("playMove win1 col", "[Game]") {
  Game game;
  std::vector<int> js {
    2, 3, 
    2, 3, 
    2, 3, 
    2
  };
  const bool res = playMoves(game, js);
  REQUIRE( res == true );
  REQUIRE( game.status() == Status::Win1 );
}

TEST_CASE ("playMove tie", "[Game]") {
  Game game;
  std::vector<int> js {
    0,1,0,1,
    0,1,2,3,
    2,3,2,3,
    4,5,4,5,
    4,5,6,6,
    1,0,1,0,
    1,0,3,2,
    3,2,3,2,
    5,4,5,4,
    5,4,6,6,
    6,6
  };
  const bool res = playMoves(game, js);
  REQUIRE( res == true );
  REQUIRE( game.status() == Status::Tie );
}

TEST_CASE ("playMove win1 diag1", "[Game]") {
  Game game;
  std::vector<int> js {
    0, 1,
    1, 2,
    3, 2,
    2, 3,
    0, 3,
    3
  };
  const bool res = playMoves(game, js);
  REQUIRE( res == true );
  REQUIRE( game.status() == Status::Win1 );
}

TEST_CASE ("playMove win1 diag2", "[Game]") {
  Game game;
  std::vector<int> js {
    3, 2,
    2, 1,
    0, 1,
    1, 0,
    3, 0,
    0
  };
  const bool res = playMoves(game, js);
  REQUIRE( res == true );
  REQUIRE( game.status() == Status::Win1 );
}

TEST_CASE ("computeValidMoves", "[Game]") {
  Game game;
  auto res = game.computeValidMoves();
  std::vector<int> expected {0, 1, 2, 3, 4, 5, 6};
  REQUIRE( res == expected );
}

TEST_CASE ("plays + computeValidMoves", "[Game]") {
  Game game;
  std::vector<int> js {
    1, 1,
    1, 1,
    1, 1
  };
  playMoves(game, js);
  auto res = game.computeValidMoves();
  std::vector<int> expected {0, 2, 3, 4, 5, 6};
  REQUIRE( res == expected );
}


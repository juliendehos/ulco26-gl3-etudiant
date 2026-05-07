
#include "Game.hpp"

#include <catch2/catch_test_macros.hpp>

///////////////////////////////////////////////////////////////////////////////
// helpers
///////////////////////////////////////////////////////////////////////////////

bool playMoves(Game & game, const std::vector<int> & js) {
  for (const int j : js) {
    const bool res = game.play(j);
    if (not res)
      return false;
  }
  return true;
}

///////////////////////////////////////////////////////////////////////////////
// test Game methods
///////////////////////////////////////////////////////////////////////////////

TEST_CASE ("newGame 1", "[connect4]") {

  Game game;
  REQUIRE( game.getStatus() == Status::Play1 );

  for (int i=0; i<N_ROWS; i++) {
    for (int j=0; j<N_COLS; j++) {
      REQUIRE( game.getCell(i, j) == Cell::Empty );
    }
  }

}

TEST_CASE ("newGame 2", "[connect4]") {

  Game game;
  game.newGame();
  REQUIRE( game.getStatus() == Status::Play2 );

  for (int i=0; i<N_ROWS; i++) {
    for (int j=0; j<N_COLS; j++) {
      REQUIRE( game.getCell(i, j) == Cell::Empty );
    }
  }

}

TEST_CASE ("play ok", "[connect4]") {

  Game game;
  const bool res = game.play(1);
  REQUIRE( res == true );
  REQUIRE( game.getStatus() == Status::Play2 );

  for (int i=0; i<N_ROWS; i++) {
    for (int j=0; j<N_COLS; j++) {
      if (i==0 and j==1) {
        REQUIRE( game.getCell(0, 1) == Cell::Player1 );
      }
      else {
        REQUIRE( game.getCell(i, j) == Cell::Empty );
      }
    }
  }

}

TEST_CASE ("play ko", "[connect4]") {

  Game game;
  const bool res = game.play(42);
  REQUIRE( res == false );
  REQUIRE( game.getStatus() == Status::Play1 );

  for (int i=0; i<N_ROWS; i++) {
    for (int j=0; j<N_COLS; j++) {
      REQUIRE( game.getCell(i, j) == Cell::Empty );
    }
  }

}

TEST_CASE ("play win1, stop", "[connect4]") {
  Game game;
  std::vector<int> js {
    1, 1,
    2, 2,
    3, 3,
    4
  };
  playMoves(game, js);
  const bool res = game.play(4);
  REQUIRE( res == false );
  REQUIRE( game.getStatus() == Status::Win1 );
}

TEST_CASE ("play win2, stop", "[connect4]") {
  Game game;
  game.newGame();
  std::vector<int> js {
    1, 1,
    2, 2,
    3, 3,
    4
  };
  playMoves(game, js);
  const bool res = game.play(4);
  REQUIRE( res == false );
  REQUIRE( game.getStatus() == Status::Win2 );
}

TEST_CASE ("full column", "[connect4]") {
  Game game;
  std::vector<int> js {
    1, 1,
    1, 1,
    1, 1,
  };
  const bool res1 = playMoves(game, js);
  REQUIRE( res1 == true );
  const bool res2 = game.play(1);
  REQUIRE( res2 == false );
  REQUIRE( game.getStatus() == Status::Play1 );
}

///////////////////////////////////////////////////////////////////////////////
// test game scenarios
///////////////////////////////////////////////////////////////////////////////

TEST_CASE ("play win1 row", "[connect4]") {
  Game game;
  std::vector<int> js {
    1, 1,
    2, 2,
    3, 3,
    4
  };
  const bool res = playMoves(game, js);
  REQUIRE( res == true );
  REQUIRE( game.getStatus() == Status::Win1 );
}

TEST_CASE ("play win1 col", "[connect4]") {
  Game game;
  std::vector<int> js {
    2, 3, 
    2, 3, 
    2, 3, 
    2
  };
  const bool res = playMoves(game, js);
  REQUIRE( res == true );
  REQUIRE( game.getStatus() == Status::Win1 );
}

TEST_CASE ("play tie", "[connect4]") {
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
  REQUIRE( game.getStatus() == Status::Tie );
}

TEST_CASE ("play win1 diag1", "[connect4]") {
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
  REQUIRE( game.getStatus() == Status::Win1 );
}

TEST_CASE ("play win1 diag2", "[connect4]") {
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
  REQUIRE( game.getStatus() == Status::Win1 );
}

TEST_CASE ("computeValidMoves", "[connect4]") {
  Game game;
  auto res = game.computeValidMoves();
  std::vector<int> expected {0, 1, 2, 3, 4, 5, 6};
  REQUIRE( res == expected );
}

TEST_CASE ("plays + computeValidMoves", "[connect4]") {
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


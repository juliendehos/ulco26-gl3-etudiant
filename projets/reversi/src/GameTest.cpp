
#include "Game.hpp"

#include <catch2/catch_test_macros.hpp>

#include <sstream>

///////////////////////////////////////////////////////////////////////////////
// helpers
///////////////////////////////////////////////////////////////////////////////

std::string fmtMoves(const Moves & ms) {
  std::ostringstream oss;
  for (const auto &[p0, ps] : ms) {
    oss << p0.first << "," << p0.second << ":";
    for (const auto p : ps) {
      oss << " " << p.first << "," << p.second;
    }
    oss << "\n";
  }
  return oss.str();
}

///////////////////////////////////////////////////////////////////////////////
// test Game methods
///////////////////////////////////////////////////////////////////////////////

TEST_CASE ("constructor", "[Game]") {
  // TODO
  // status
  // cells
}


TEST_CASE ("playMove 2-3", "[Game]") {
  // TODO
  // status
  // cells
}

TEST_CASE ("playMove 2-3 2-4", "[Game]") {
  // TODO
  // status
  // cells
}

TEST_CASE ("valid moves, initial", "[Game]") {

  const Moves expected = {
    {{2,3}, {{3,3}}},
    {{3,2}, {{3,3}}},
    {{4,5}, {{4,4}}},
    {{5,4}, {{4,4}}},
  };

  // TODO
  // valid moves
}

TEST_CASE ("valid moves, playMove 2-3", "[Game]") {

  const Moves expected = {
    {{2,2}, {{3,3}}},
    {{2,4}, {{3,4}}},
    {{4,2}, {{4,3}}},
  };

  // TODO
  // valid moves
}


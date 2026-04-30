#include "Game.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

bool operator==(const Position & p1, const Position & p2) {
  return p1.i == p2.i and p1.j == p2.j;
}

Game::Game(flecs::world & ecs, const std::string & dataDir) :
  _ecs(ecs), 
  _filenames({
    dataDir + "maze1.txt",
    dataDir + "maze2.txt",
    dataDir + "maze3.txt",
    dataDir + "maze4.txt"
  })
{
  _ecs.set(Level{0});
  loadLevel();
}

void Game::loadLevel() {

  // clear previous data
  _ecs.each([](flecs::entity e, const Wall) { e.destruct(); });
  _ecs.each([](flecs::entity e, const Target) { e.destruct(); });
  _ecs.each([](flecs::entity e, const Player) { e.destruct(); });

  // get maze filename
  const Level & level = _ecs.get<Level>();
  const std::string & filename = _filenames[level.value];
  
  // load maze
  try {
    std::string line;
    std::ifstream ifs(filename);

    // read header (ni, nj, i0, j0)
    std::getline(ifs, line);
    std::istringstream issHeader(line);
    int ni, nj;
    issHeader >> ni >> nj;
    _ecs.set(Maze{ni, nj});

    // read maze
    for (int i=0; i<ni; i++) {
      std::getline(ifs, line);
      std::istringstream iss(line);

      for (int j=0; j<nj; j++) {
        const char c = iss.get();
        if (c == '+') {
          _ecs.entity().add<Wall>().set(Position{i, j});
        }
        else if (c == '?') {
          _ecs.entity().add<Target>().set(Position{i, j});
        }
        else if (c == 'o') {
          _player = _ecs.entity().add<Player>().set(Position{i, j});
        }
      }
    }

  }
  catch(...) {
    std::cerr << "Cannot read " << filename << std::endl;
  }

}

void Game::playMove(const Move move) {

  Position & pos = _player.get_mut<Position>();
  Position newPos = pos;

  // move position pos
  switch (move) {
    case Move::Up:    newPos.i--;  break;
    case Move::Down:  newPos.i++;  break;
    case Move::Left:  newPos.j--;  break;
    case Move::Right: newPos.j++;  break;
  }

  // wrap maze
  const auto [ni, nj] = _ecs.get<Maze>();
  if (newPos.i < 0)     newPos.i = ni-1;
  if (newPos.i >= ni)   newPos.i = 0;
  if (newPos.j < 0)     newPos.j = nj-1;
  if (newPos.j >= nj)   newPos.j = 0;

  // handle target
  auto queryTarget = _ecs.query<Target, Position>();
  flecs::entity entityTarget = queryTarget.find([&newPos](const Target, const Position & p) { return newPos == p; });
  if (entityTarget) {
    Level & level = _ecs.get_mut<Level>();
    level.value = (level.value + 1) % _filenames.size();
    loadLevel();
  }
  else {

    // handle wall
    auto queryWall = _ecs.query<Wall, Position>();
    flecs::entity entityWall = queryWall.find([&newPos](const Wall, const Position & p) { return newPos == p; });
    if (entityWall) {
      newPos = pos;
    }

    // set new pos
    pos = newPos;
  }
}


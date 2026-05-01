#pragma once

#include <flecs.h>

#include <random>

///////////////////////////////////////////////////////////////////////////////
// params
///////////////////////////////////////////////////////////////////////////////

const float gGameWidth = 1200;
const float gGameHeight = 800;

const float gGameShipFriction = 0.1;
const float gGameShipDirectionSpeed = 5;
const float gGameShipThrust = 800;
const float gGameShipCollisionDistance = 70;
const float gGameShipMaxVelocity = 600;

const float gGameAsteroidDistance = 300;
const float gGameAsteroidXi = 0.005;
const float gGameAsteroidMaxSpeed = 200;
const int gGameMaxAsteroids = 6;
const int gGameMinAsteroids = 2;

const float gGameBulletOffset = 50;
const float gGameBulletSpeed = 500;
const float gGameBulletLifeTime = 2;
const float gGameBulletDistance = 50;


///////////////////////////////////////////////////////////////////////////////
// components
///////////////////////////////////////////////////////////////////////////////

struct Asteroid {};

struct Bullet {};

struct LifeTime {
  float value;
};

struct Position {
  float x, y;
};

struct Velocity {
  float x, y;
};

// TODO components

///////////////////////////////////////////////////////////////////////////////
// game
///////////////////////////////////////////////////////////////////////////////

class Rng {
  private:
    std::default_random_engine _engine;
    std::uniform_real_distribution<float> _dist;
  public:
    Rng(const float min, const float max);
    float operator()();
};

class Game {
  private:
    flecs::world & _ecs;
    flecs::entity _spaceship;

    Rng _rngAsteroid;
    Rng _rngPosX;
    Rng _rngPosY;
    Rng _rngVel;
    Rng _rngDir;

  public:
    // inits
    Game(flecs::world & ecs);
    Game(const Game &) = delete;

    // updates
    void updateMoves(const float dt);
    void updatePhysics(const float dt);
    void updateData(const float dt);

    // user moves
    void moveLeft(bool v);
    void moveRight(bool v);
    void moveForward(bool v);
    void moveFire();
    void moveLoad();

  private:
    void reset();
    int countAsteroids() const;
    void createAsteroids();
    float computeDistance(const Position & p1, const Position & p2) const;
    float computeNorm(const Velocity & p) const;

};



#include "Game.hpp"

#include <numbers>

Rng::Rng(const float min, const float max) :
  _engine(std::random_device{}()),
  _dist(min, max)
{
}

float Rng::operator()() {
  return _dist(_engine);
}

Game::Game(flecs::world & ecs) :
  _ecs(ecs),
  _rngAsteroid(0, 1),
  _rngPosX(0, gGameWidth),
  _rngPosY(0, gGameHeight),
  _rngVel(-gGameAsteroidMaxSpeed, gGameAsteroidMaxSpeed),
  _rngDir(0, 2*std::numbers::pi)
{
  _spaceship = _ecs.entity("spaceship");

  // TODO [Step6] score

  reset();
}

void Game::reset() {

  // TODO [Step3] asteroid

  // TODO [Step4] bullets

  // TODO [Step1] spaceship

  // TODO [Step6] score

}

void Game::moveLeft(bool v) {
  // TODO [Step1] spaceship
}

void Game::moveRight(bool v) {
  // TODO [Step1] spaceship
}

void Game::moveForward(bool v) {
  // TODO [Step1] spaceship
}

void Game::moveFire() {
  // TODO [Step4] spaceship
  // activer fire
}

void Game::moveLoad() {
  // TODO [Step4] spaceship
  // désactiver fire
  // activer load
}

void Game::updateMoves(const float dt) {

  // TODO [Step1] direction
  // left -> - dt * gGameShipDirectionSpeed
  // right -> ...

  // TODO [Step1] forward
  // vx += dt * cos * gGameShipThrust
  // vy -= dt * sin * gGameShipThrust
  // et vérifier la norme du vecteur vitesse (<= gGameShipMaxVelocity)

  // TODO [Step4] fire -> create a bullet
  // vx = sin
  // vy = -cos

}

void Game::updatePhysics(const float dt) {

  // TODO [Step1] motion

  // TODO [Step1] friction

  // wrap positions
  // les asteroids et le spaceship passent d'un bord à l'autre mais pas les bullets
  auto wrapQuery =  _ecs.query_builder<Position &>()
    .without<Bullet>()
    .build()
    ;
  wrapQuery.each([dt](Position & pos) {
      pos.x = pos.x <= gGameWidth ? pos.x : 0;
      pos.x = pos.x >= 0 ? pos.x : gGameWidth;
      pos.y = pos.y <= gGameHeight ? pos.y : 0;
      pos.y = pos.y >= 0 ? pos.y : gGameHeight;
  });

  // TODO [Step3] collisions spaceship/asteroid
  // rechercher une collision (distance < gGameShipCollisionDistance)
  // faire un reset si collision

  // TODO [Step5] collisions bullet/asteroid
  // si collision : supprimer les 2 entités
  // TODO [Step6] maj le score si collision bullet/asteroid

}

float Game::computeDistance(const Position & p1, const Position & p2) const {
  const float dx = p1.x - p2.x;
  const float dy = p1.y - p2.y;
  return std::sqrt(dx*dx + dy*dy);
}

float Game::computeNorm(const Velocity & v) const {
  return std::sqrt(v.x*v.x + v.y*v.y);
}

void Game::updateData(const float dt) {

  // asteroids
  const int nbAsteroids = countAsteroids();
  if (nbAsteroids < gGameMinAsteroids) {
    createAsteroids();
  }
  else if (nbAsteroids < gGameMaxAsteroids) {
    float xi = _rngAsteroid();
    if (xi < gGameAsteroidXi) {
      createAsteroids();
    }
  }

  // bullets
  _ecs.each([dt](flecs::entity e, LifeTime & t) {
    t.value -= dt;
    if (t.value < 0) e.destruct();
  });

}

void Game::createAsteroids() {

  // TODO [Step2] position
  // vérifier que la position est sufffisamment éloignée de spaceship (gGameAsteroidDistance)

  // TODO [Step2] velocity

  // TODO [Step2] direction

  // TODO [Step2] entity

}

int Game::countAsteroids() const {
  flecs::entity asteroid = _ecs.component<Asteroid>();
  return _ecs.count(asteroid);
}


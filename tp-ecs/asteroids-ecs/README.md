
# asteroids-ecs

## Description

Une implémentation simplifiée du jeu
[Asteroids](https://fr.wikipedia.org/wiki/Asteroids).

Mouvements :
    - direction : flêches gauche/droite
    - avancer : flêche haut
    - tirer : espace

Calcul du score:
    - destruction asteroid: +1
    - collision asteroid: /2

## Modélisation

Architecture Entity-Component-System.

- Components:
    - Position: x, y
    - Direction: x, y
    - Velocity: x, y
    - Friction: value
    - Move: left, right, forward, fire, loaded
    - LifeTime: value
    - Spaceship
    - Asteroid
    - Bullet
    - Score: value

- Entities:
    - global: Score
    - spaceship: Spaceship, Position, Direction, Velocity, Friction, Move
    - asteroid: Asteroid, Position, Velocity, Direction
    - bullet: Bullet, Position, Velocity, LifeTime

- Systems:
    - events
    - update
    - draw

## Planning

- [ ] Step1 : spaceship (maj, déplacement, affichage)
- [ ] Step2 : asteroids (sans collisions)
- [ ] Step3 : collisions spaceship/asteroid
- [ ] Step4 : bullets (sans collisions)
- [ ] Step5 : collisions bullet/asteroid
- [ ] Step6 : score


# test-ecs

## Description

A simple application using [flecs](https://www.flecs.dev). 

## Components

- Position: x, y

- Velocity: x, y

- Life: value

- Player, Enemy, Wall

## Entities

- player1:
    - position 20 10
    - velocity 1 2
    - life 50

- enemy1:
    - position 50 20
    - life 100

- wall1:
    - position 10 0

- wall2:
    - position 100 20

## Systems

- update position (pos += vel)

- print position

- print walls

- print lifes

## Expected output

```
******************************
- player1: 21 12
- enemy1: 50 20
- wall1: 10 0
- wall2: 100 20
WALLS: 10 0; 100 20; 
LIFES: player1 50; enemy1 100; 
******************************
- player1: 22 14
- enemy1: 50 20
- wall1: 10 0
- wall2: 100 20
WALLS: 10 0; 100 20; 
LIFES: player1 50; enemy1 100; 
******************************
- player1: 23 16
- enemy1: 50 20
- wall1: 10 0
- wall2: 100 20
WALLS: 10 0; 100 20; 
LIFES: player1 50; enemy1 100; 
******************************
```


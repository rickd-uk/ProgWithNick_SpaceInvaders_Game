#pragma once
#include "alien.hpp"
#include "mysteryship.hpp"
#include "obstacle.hpp"
#include "spaceship.hpp"

class Game {
 public:
  Game();
  ~Game();
  void Draw();
  void Update();
  void HandleInput();

 private:
  Spaceship spaceship;
  MysteryShip mysteryship;

  void MoveAliens();
  void MoveAliensDown(int distance);
  void AlienShootLaser();
  std::vector<Alien> CreateAliens();
  std::vector<Obstacle> CreateObstacles();
  std::vector<Obstacle> obstacles;
  std::vector<Alien> aliens;
  std::vector<Laser> alienLasers;

  constexpr static float alienLaserShootInterval = 0.35;
  int aliensDirection;
  float timeLastAlienFired;
  void DeleteInactiveLasers();

  float mysteryShipSpawnInterval;
  float timeLastShipSpawn;
};

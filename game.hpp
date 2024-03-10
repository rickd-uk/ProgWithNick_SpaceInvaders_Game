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
  bool running;

 private:
  MysteryShip mysteryship;

  void MoveAliens();
  void MoveAliensDown(int distance);
  void AlienShootLaser();
  void CheckForCollisions();
  void GameOver();
  void Reset();
  void InitGame();
  void DeleteInactiveLasers();

  Spaceship spaceship;
  std::vector<Alien> CreateAliens();
  std::vector<Obstacle> CreateObstacles();
  std::vector<Obstacle> obstacles;
  std::vector<Alien> aliens;
  std::vector<Laser> alienLasers;

  constexpr static float alienLaserShootInterval = 0.35;
  constexpr static int obstacleyOffset = 200;
  int aliensDirection;
  float timeLastAlienFired;
  float mysteryShipSpawnInterval;
  float timeLastShipSpawn;
  int lives;
};

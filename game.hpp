#pragma once
#include "alien.hpp"
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
  void DeleteInactiveLasers();
  Spaceship spaceship;

  void MoveAliens();
  void MoveAliensDown(int distance);
  std::vector<Alien> CreateAliens();
  std::vector<Obstacle> CreateObstacles();
  std::vector<Obstacle> obstacles;
  std::vector<Alien> aliens;
  int aliensDirection;
};

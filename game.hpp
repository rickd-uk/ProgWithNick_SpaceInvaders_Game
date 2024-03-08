#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"

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

  std::vector<Alien> CreateAliens();
  std::vector<Obstacle> CreateObstacles();
  std::vector<Obstacle> obstacles;
  std::vector<Alien> aliens;
};

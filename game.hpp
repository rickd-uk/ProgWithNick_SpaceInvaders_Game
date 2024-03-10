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
  int GetLives() const;
  int GetScore() const;
  int GetHighScore() const;

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
  void CheckForHighScore();
  void SaveHighScoreToFile(int highScore);
  int LoadHighScoreFromFile();

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
  int score;
  int highScore;
};

#include "game.hpp"

#include <fstream>
#include <iostream>

#include "spaceship.hpp"

Game::Game() {
    music = LoadMusicStream("sounds/music.ogg");
    PlayMusicStream(music);
    InitGame();
}

Game::~Game() {
    Alien::UnloadImages();
    UnloadMusicStream(music);
}

int Game::GetLives() const { return lives; }

int Game::GetScore() const { return score; }

int Game::GetHighScore() const { return highScore; }

void Game::Update() {
    if (running) {
        double currentTime = GetTime();
        if (currentTime - timeLastShipSpawn > mysteryShipSpawnInterval) {
            mysteryship.Spawn();
            timeLastShipSpawn = GetTime();
            mysteryShipSpawnInterval = GetRandomValue(10, 20);
        }
        for (auto &laser : spaceship.lasers) {
            laser.Update();
        }
        DeleteInactiveLasers();
        // std::cout << "Lasers Size: " << spaceship.lasers.size() << std::endl;
        MoveAliens();

        AlienShootLaser();

        for (auto &laser : alienLasers) {
            laser.Update();
        }
        mysteryship.Update();

        CheckForCollisions();
    } else {
        if (IsKeyDown(KEY_ENTER)) {
            Reset();
            InitGame();
        }
    }
}

void Game::Draw() {
    spaceship.Draw();
    for (auto &laser : spaceship.lasers) {
        laser.Draw();
    }
    for (auto &obstacle : obstacles) {
        obstacle.Draw();
    }

    for (auto &alien : aliens) {
        alien.Draw();
    }

    for (auto &laser : alienLasers) {
        laser.Draw();
    }
    mysteryship.Draw();
}

void Game::HandleInput() {
    if (running) {
        if (IsKeyDown(KEY_LEFT)) {
            spaceship.MoveLeft();
        } else if (IsKeyDown(KEY_RIGHT)) {
            spaceship.MoveRight();
        } else if (IsKeyDown(KEY_SPACE)) {
            spaceship.FireLaser();
        }
    }
}

void Game::DeleteInactiveLasers() {
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
        if (!it->IsActive()) {
            it = spaceship.lasers.erase(it);
        } else {
            ++it;
        }
    }
    for (auto it = alienLasers.begin(); it != alienLasers.end();) {
        if (!it->IsActive()) {
            it = alienLasers.erase(it);
        } else {
            ++it;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles() {
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - float(4 * obstacleWidth)) / 5;
    for (int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - obstacleyOffset)}));
    }
    return obstacles;
}

std::vector<Alien> Game::CreateAliens() {
    int cellSize = 55;
    std::vector<Alien> aliens;

    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 11; col++) {
            int alienType;
            if (row == 0) {
                alienType = 3;
            } else if (row == 1 | row == 2) {
                alienType = 2;
            } else {
                alienType = 1;
            }
            float x = 75 + col * cellSize;
            float y = 110 + row * cellSize;

            aliens.push_back(Alien(alienType, {x, y}));
        }
    }
    return aliens;
}

void Game::MoveAliens() {
    for (auto &alien : aliens) {
        if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - G_BORDER_OFFSET) {
            aliensDirection = -1;
            MoveAliensDown(10);
        }
        if (alien.position.x < G_BORDER_OFFSET) {
            aliensDirection = 1;
            MoveAliensDown(10);
        }
        alien.Update(aliensDirection);
    }
}

void Game::MoveAliensDown(int distance) {
    for (auto &alien : aliens) {
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser() {
    double currentTime = GetTime();
    if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()) {
        int randIndex = GetRandomValue(0, aliens.size() - 1);
        Alien &alien = aliens[randIndex];

        float alienXPos = alien.position.x + (float)alien.alienImages[alien.type - 1].width / 2;
        float alienYPos = alien.position.y + alien.alienImages[alien.type - 1].height;
        alienLasers.push_back(Laser({alienXPos, alienYPos}, -6));

        timeLastAlienFired = GetTime();
    }
}

void Game::CheckForCollisions() {
    // Spaceship Lasers
    for (auto &laser : spaceship.lasers) {
        auto it = aliens.begin();
        while (it != aliens.end()) {
            // Check if player hits an alien
            if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                if (it->type == 1) {
                    score += 100;
                } else if (it->type == 2) {
                    score += 150;
                } else if (it->type == 3) {
                    score += 200;
                }

                CheckForHighScore();

                it = aliens.erase(it);
                laser.SetActive(false);
            } else {
                ++it;
            }
        }

        for (auto &obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    it = obstacle.blocks.erase(it);
                    laser.SetActive(false);
                } else {
                    ++it;
                }
            }
        }

        // Check if player hit mysteryship
        if (CheckCollisionRecs(mysteryship.getRect(), laser.getRect())) {
            score += 500;
            CheckForHighScore();

            mysteryship.alive = false;
            laser.SetActive(false);
        }
    }

    // Alien lasers

    for (auto &laser : alienLasers) {
        if (CheckCollisionRecs(laser.getRect(), spaceship.getRect())) {
            laser.SetActive(false);
            lives--;
            if (lives == 0)
                GameOver();
        }

        // TODO: Duplicated code from above - must refactor
        for (auto &obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    it = obstacle.blocks.erase(it);
                    laser.SetActive(false);
                } else {
                    ++it;
                }
            }
        }
    }

    // Alien collision with obstacle
    for (auto &alien : aliens) {
        for (auto &obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), alien.getRect())) {
                    it = obstacle.blocks.erase(it);

                } else {
                    it++;
                }
            }
        }
        if (CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
            GameOver();
        }
    }
}

void Game::GameOver() { running = false; }

void Game::InitGame() {
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0f;
    timeLastShipSpawn = 0.0;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);

    running = true;
    score = 0;
    highScore = LoadHighScoreFromFile();
    lives = 3;
}

void Game::CheckForHighScore() {
    if (score > highScore) {
        highScore = score;
        SaveHighScoreToFile(highScore);
    }
}

void Game::SaveHighScoreToFile(int highScore) {
    std::ofstream highScoreFile("highscore.txt");

    if (highScoreFile.is_open()) {
        highScoreFile << highScore;
        highScoreFile.close();
    } else {
    std:
        std::cerr << "Failed to save highScore to file!" << std::endl;
    }
}

int Game::LoadHighScoreFromFile() {
    int loadedHighScore = 0;
    std::ifstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open()) {
        highScoreFile >> loadedHighScore;
        highScoreFile.close();
    } else {
        std::cerr << "Failed to load highScoreFile from file!" << std::endl;
    }
    return loadedHighScore;
}

void Game::Reset() {
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
}


#ifndef SPACE_SHOOTER_GAME_H
#define SPACE_SHOOTER_GAME_H

#include "Grid.h"
#include "AssetManager.h"
#include "Window.h"
#include "Planet.h"

#include <algorithm>
class Game {
public:
    Game();
    void run();

private:
    void update();
    void render();
    void gameOver();

    void updatePlayer(float deltaTime);
    void updateEnemies(float deltaTime);
    void updateSpaceObjects(float deltaTime);
    void updateBullets();
    void updatePowerups();
    void updateGui(float deltaTime);

    bool getPlayerCollision();
    void calculateCameraPosition();
    void setGui();

    sf::Vector2f randomSpawnPoint();
    sf::Clock updateClock_;

    Window window_;
    Grid grid_;
    AssetManager assets_;
    std::shared_ptr<Player> player_;
    std::vector<Enemy> enemies_;
    std::vector<Bullet> playerBullets_;
    std::vector<Bullet> enemyBullets_;
    std::vector<Powerup> powerups_;
    std::vector<std::shared_ptr<SpaceObject>> spaceObjects_;

    sf::Vector2f spaceObjectsNetForce_;
    sf::Vector2f cameraPosition_;
    sf::Sprite backgroundSprite_;
    sf::Sprite heartSprite_;

    sf::Text fpsText_;
    sf::Text killCounterText_;
    sf::Text finalScreenText_;
    sf::Text debugText_;

    sf::Clock collisionTimer_;

    float playerBulletSpeed_;
    float enemyBulletSpeed_;
    float powerupSpeed_;
    float shootTimePlayer_;
    float shootTimeEnemy_;
    float cameraAcceleration_;
    uint killCounter_;
};

#endif //SPACE_SHOOTER_GAME_H

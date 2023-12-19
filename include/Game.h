#ifndef SPACE_SHOOTER_GAME_H
#define SPACE_SHOOTER_GAME_H

#include "Grid.h"
#include "AssetManager.h"
#include "EnemyManager.h"
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
    void updateBullets(float deltaTime);
    void updatePowerups(float deltaTime);
    void updateGui(float deltaTime);

    bool getPlayerCollision();
    void calculateCameraPos();
    void setGui();

    sf::Vector2f randomSpawnPoint();
    sf::Clock updateClock_;

    Window window_;
    Grid grid_;
    AssetManager assets_;
    EnemyManager enemyManager_;
    std::shared_ptr<Player> player_;
    std::vector<Enemy> enemies_;
    std::vector<Bullet> playerBullets_;
    std::vector<Bullet> enemyBullets_;
    std::vector<Powerup> powerups_;
    std::vector<std::shared_ptr<SpaceObject>> spaceObjects_;

    sf::Vector2f spaceObjectsNetForce_;
    sf::Vector2f cameraPos_;
    sf::Sprite backgroundSprite_;
    sf::Sprite heartSprite_;

    sf::Vector2f playerBulletSpawnOffset_;

    sf::Text fpsText_;
    sf::Text killCounterText_;
    sf::Text finalScreenText_;
    sf::Text debugText_;

    sf::Clock collisionTimer_;

    float shootTimePlayer_;
    float shootTimeEnemy_;
    float cameraAcc_;
    uint killCounter_;
};

#endif //SPACE_SHOOTER_GAME_H

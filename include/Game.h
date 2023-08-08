#ifndef SPACE_SHOOTER_GAME_H
#define SPACE_SHOOTER_GAME_H

#include "Grid.h"
#include "AssetManager.h"
#include "Window.h"
#include "Planet.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"
#include "PowerupManager.h"
#include "SpaceObjectManager.h"
#include "UIManager.h"
#include "CollisionManager.h"

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
    void updateSpaceObjects(float deltaTime);
    void updateBullets(float deltaTime);
    void updatePowerups(float deltaTime);
    void updateGui(float deltaTime);

    bool getPlayerCollision();
    void calculateCameraPosition();
    void setGui();

    sf::Clock updateClock_;

    Window window_;
    Grid grid_;
    AssetManager assets_;
    EnemyManager enemyManager_;
    std::shared_ptr<Player> player_;
    std::vector<Bullet> playerBullets_;
    std::vector<Bullet> enemyBullets_;
    std::vector<Powerup> powerups_;
    std::vector<std::shared_ptr<SpaceObject>> spaceObjects_;

    sf::Vector2f spaceObjectsNetForce_;
    sf::Vector2f cameraPosition_;
    sf::Sprite backgroundSprite_;
    sf::Sprite heartSprite_;

    sf::Vector2f playerBulletSpawnOffset_;
    sf::Vector2f enemyBulletSpawnOffset_;

    sf::Text fpsText_;
    sf::Text killCounterText_;
    sf::Text finalScreenText_;
    sf::Text debugText_;

    sf::Clock collisionTimer_;

    float shootTimePlayer_;
    float cameraAcceleration_;
    uint killCounter_;
};

#endif //SPACE_SHOOTER_GAME_H

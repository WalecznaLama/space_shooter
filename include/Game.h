#ifndef SPACE_SHOOTER_GAME_H
#define SPACE_SHOOTER_GAME_H

#include "Manager/AssetManager.h"
#include "Manager/CollisionManager.h"

#include "Window.h"
#include <algorithm>

class Game {
public:
    Game();
    void run();

private:
    void update();
    void render();
    void gameOver();

    void updateGui(float deltaTime);

    void calculateCameraPos();
    void setGui();

    sf::Clock updateClock_;

    Window window_;
    Grid grid_;
    AssetManager assets_;
    EnemyManager enemyManager_;
    ProjectileManager projectileManager_;
    PowerupManager powerupManager_;
    SpaceObjectManager spaceObjectManager_;
    CollisionManager collisionManager_;
    PlayerManager playerManager_;

    sf::Vector2f cameraPos_;
    sf::Sprite backgroundSprite_;
    sf::Sprite heartSprite_;

    sf::Text fpsText_;
    sf::Text killCounterText_;
    sf::Text finalScreenText_;
    sf::Text debugText_;

    float cameraAcc_;
};

#endif //SPACE_SHOOTER_GAME_H

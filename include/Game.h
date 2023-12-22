#ifndef SPACE_SHOOTER_GAME_H
#define SPACE_SHOOTER_GAME_H

#include "AssetManager.h"
#include "EnemyManager.h"
#include "PlayerManager.h"
#include "ProjectileManager.h"
#include "SpaceObjectManager.h"
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

    void updatePowerups(float deltaTime);
    void updateGui(float deltaTime);

    void calculateCameraPos();
    void setGui();

    sf::Clock updateClock_;

    Window window_;
    Grid grid_;
    AssetManager assets_;
    EnemyManager enemyManager_;
    ProjectileManager projectileManager_;
    SpaceObjectManager spaceObjectManager_;
    PlayerManager playerManager_;
    std::vector<Powerup> powerups_;

    sf::Vector2f cameraPos_;
    sf::Sprite backgroundSprite_;
    sf::Sprite heartSprite_;

    sf::Text fpsText_;
    sf::Text killCounterText_;
    sf::Text finalScreenText_;
    sf::Text debugText_;

    float cameraAcc_;
    uint killCounter_;
};

#endif //SPACE_SHOOTER_GAME_H

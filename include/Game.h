#ifndef SPACE_SHOOTER_GAME_H
#define SPACE_SHOOTER_GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "AssetManager.h"
#include "Powerup.h"

class Game {
public:
    Game();
    void run();

private:
    void update();
    void render();
    void gameOver();
    void updateEnemies();
    void checkBulletEnemyCollisions();
    void removeEnemiesOffScreen();
    void enemiesShoot();

    void bullets_update();
    void powerups_update();


    sf::RenderWindow window;
    AssetManager assets;
    Player player;
    std::vector<Enemy> enemies;
    std::vector<Bullet> playerBullets;
    std::vector<Bullet> enemyBullets;
    std::vector<Powerup> powerups;

    sf::Sprite backgroundSprite;

    sf::Text fpsText;
    sf::Text killCounterText;

    sf::Vector2f player_speed;
    sf::Vector2f enemy_speed;
    float player_bullet_speed;
    float enemy_bullet_speed;
    float shoot_time_player;
    float shoot_time_enemy;
    uint kill_counter = 0;
    int framerate;
};

#endif //SPACE_SHOOTER_GAME_H

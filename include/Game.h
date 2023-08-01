#ifndef SPACE_SHOOTER_GAME_H
#define SPACE_SHOOTER_GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "AssetManager.h"

class Game {
public:
    Game();
    void run();

private:
    void update();
    void render();
    void checkPlayerCollision();
    void gameOver();
    void updateEnemies();
    void checkBulletEnemyCollisions();
    void removeEnemiesOffScreen();
    void enemiesShoot();

    sf::RenderWindow window;
    AssetManager assets;
    Player player;
    std::vector<Enemy> enemies;
    std::vector<Bullet> playerBullets;
    std::vector<Bullet> enemyBullets;
    sf::Texture playerTexture;
    sf::Texture enemyTexture;
    sf::Texture playerBulletTexture;
    sf::Texture enemyBulletTexture;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Font font;
    sf::Text fpsText;
    sf::Text killCounterText;

    float player_bullet_speed;
    float enemy_bullet_speed;
    uint kill_counter = 0;
    bool is_game_over = false;
};

#endif //SPACE_SHOOTER_GAME_H

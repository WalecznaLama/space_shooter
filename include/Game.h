#ifndef SPACE_SHOOTER_GAME_H
#define SPACE_SHOOTER_GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class Game {
public:
    Game();
    void run();

private:
    void update();
    void render();

    sf::RenderWindow window;
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
    uint kill_counter;
};

#endif //SPACE_SHOOTER_GAME_H

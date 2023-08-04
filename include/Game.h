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

    void enemiesShoot();
    void bullets_update();
    void powerups_update();

    sf::RenderWindow window_;
    AssetManager assets_;
    std::unique_ptr<Player> player_;
    std::vector<Enemy> enemies_;
    std::vector<Bullet> playerBullets_;
    std::vector<Bullet> enemyBullets_;
    std::vector<Powerup> powerups_;

    sf::Sprite backgroundSprite_;

    sf::Text fpsText_;
    sf::Text killCounterText_;

    sf::Vector2f enemySpeed_;
    float player_bullet_speed_;
    float enemy_bullet_speed_;
    float powerup_speed_;
    float shoot_time_player_;
    float shoot_time_enemy_;
    uint kill_counter_ = 0;
    int framerate_;
};

#endif //SPACE_SHOOTER_GAME_H

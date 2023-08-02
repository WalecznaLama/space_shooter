#ifndef SPACE_SHOOTER_ENEMY_H
#define SPACE_SHOOTER_ENEMY_H

#include <SFML/Graphics.hpp>
#include "Bullet.h"

class Enemy {
public:
    Enemy(const sf::Vector2u& windowSize,  const sf::Texture& texture);
    void draw(sf::RenderWindow& window) const;
    void update(float dx, float speed, sf::Vector2f player_position,
                std::vector<Bullet>& playerBullets);
    sf::Vector2f getPosition();
    bool canShoot(float time_to_shoot);
    const sf::Sprite& getSprite() const;

    bool alive = true;
    bool killed_by_player = false;

private:
    sf::Sprite sprite;
    sf::Clock shootClock;
    bool first_shot_fired = false;
    sf::Vector2u window_size;
};

#endif //SPACE_SHOOTER_ENEMY_H

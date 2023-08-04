#ifndef SPACE_SHOOTER_ENEMY_H
#define SPACE_SHOOTER_ENEMY_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Enemy  : public Entity {
public:
    Enemy(const sf::Vector2u& windowSize, const sf::Texture& texture);
    void init(const sf::Texture& texture);
    void update(const sf::Vector2f& speed, std::vector <Bullet> &bullets);
    bool isKilledByPlayer();
    void setPlayerPosition(const sf::Vector2f& playerPosition);

private:
    sf::Vector2f playerPosition_;
    float maxTilt_;
    float acceleration_ = 0.0;
};

#endif //SPACE_SHOOTER_ENEMY_H

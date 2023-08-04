#ifndef SPACE_SHOOTER_ENEMY_H
#define SPACE_SHOOTER_ENEMY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Entity.h"

class Enemy  : public Entity {
public:
    Enemy(const sf::Vector2u& windowSize, const sf::Texture& texture);
    void init(const sf::Texture& texture);
    void update(std::vector <Bullet> &bullets, const sf::Vector2f& playerPosition);
    bool isKilledByPlayer();

private:
    void calculateVelocity(const float& lin_acc, const float& theta_acc, const float& deltaTime);
    void calculateAngularVelocity(float theta_acc, float deltaTime);
    enum Direction {
        Up,
        Down,
        Left,
        Right
    };
};

#endif //SPACE_SHOOTER_ENEMY_H

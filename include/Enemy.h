#ifndef SPACE_SHOOTER_ENEMY_H
#define SPACE_SHOOTER_ENEMY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Entity.h"

class Enemy  : public Entity {
public:
    Enemy(sf::Vector2f spawn_point, const sf::Texture& texture);
    void update(const sf::Vector2f& playerPosition, float deltaTime);
private:
    float kp_ = 1.0f; // Stała proporcjonalna
    float ki_ = 0.1f; // Stała integralna
    float integral_ = 0.0f; // Suma błędów (dla części integralnej)
};

#endif //SPACE_SHOOTER_ENEMY_H

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
    float kp_; // Stała proporcjonalna
    float ki_; // Stała integralna
    float integral_; // Suma błędów (dla części integralnej)
};

#endif //SPACE_SHOOTER_ENEMY_H

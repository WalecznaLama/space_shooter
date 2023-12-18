#ifndef SPACE_SHOOTER_ENEMY_H
#define SPACE_SHOOTER_ENEMY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Entity.h"
#include "PIDController.h"

class Enemy  : public Entity {
public:
    Enemy(sf::Vector2f spawn_point, const sf::Texture& texture);
    void update(const sf::Vector2f& playerPos, float deltaTime);

private:
    PIDController pidController_;
};

#endif //SPACE_SHOOTER_ENEMY_H

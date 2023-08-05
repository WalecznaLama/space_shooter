#ifndef SPACE_SHOOTER_ENEMY_H
#define SPACE_SHOOTER_ENEMY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Entity.h"

class Enemy  : public Entity {
public:
    Enemy(sf::Vector2f spawn_point,  const sf::Texture& texture);
    void init(const sf::Texture& texture);
    void update(const sf::Vector2f& playerPosition, float deltaTime);
    void setIsKilledByPlayer(bool isKilledByPlayer);
    bool getIsKilledByPlayer() const;

private:
    void calculateVelocity(const float& lin_acc, const float& theta_acc, const float& deltaTime);
    void calculateAngularVelocity(float theta_acc, float deltaTime);

};

#endif //SPACE_SHOOTER_ENEMY_H

#ifndef SPACE_SHOOTER_BULLET_H
#define SPACE_SHOOTER_BULLET_H

#include "Object.h"

class Bullet : public Object {

public:
    Bullet(const sf::Vector2f& pos, const sf::Vector2f& spawnOffset, const float& initRot, const sf::Texture& texture);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
};

#endif //SPACE_SHOOTER_BULLET_H

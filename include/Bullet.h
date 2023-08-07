#ifndef SPACE_SHOOTER_BULLET_H
#define SPACE_SHOOTER_BULLET_H

#include "PassiveObject.h"

class Bullet : public PassiveObject {

public:
    Bullet(const sf::Vector2f& position, const float& initRotation, const sf::Texture& texture);
    void update(float linAcc, float deltaTime) override;
};

#endif //SPACE_SHOOTER_BULLET_H

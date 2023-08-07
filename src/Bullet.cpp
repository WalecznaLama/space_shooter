#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& position, const float& initRotation, const sf::Texture& texture) {
    rotation_ = initRotation;
    position_ = position;
    maxLinVel_ = 400.;
    linAcc_ = 50.;
    mass_ = 0.1;
    spriteInit(texture);
}

void Bullet::update(float linAcc, float deltaTime) {
    updateMainSpritePosition();
    calculateLinearVelocity(deltaTime);
}

#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& position, const sf::Vector2f& spawnOffset, const float& initRotation, const sf::Texture& texture) {
    position_ = position;
    rotation_ = initRotation;
    float _rotRad = rotation_ * (M_PI / 180.);

    float offsetX = spawnOffset.x * cosf(_rotRad) - spawnOffset.y * sinf(_rotRad);
    float offsetY = spawnOffset.x * sinf(_rotRad) + spawnOffset.y * cosf(_rotRad);

    position_.x += offsetX;
    position_.y += offsetY;

    maxLinVel_ = 600.;
    linAcc_ = 200.;
    mass_ = 0.1;

    radius_ = 5;
    spriteInit(texture);
}

void Bullet::update(float deltaTime) {
    updateMainSpritePosition();
    calculateLinearVelocity(deltaTime);
}

void Bullet::draw(sf::RenderWindow &window) const {  window.draw(mainSprite_); }

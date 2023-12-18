#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& pos, const sf::Vector2f& spawnOffset, const float& initRot, const sf::Texture& texture) {
    pos_ = pos;
    rot_ = initRot;
    float _rotRad = rot_ * (M_PI / 180.);

    float offsetX = spawnOffset.x * cosf(_rotRad) - spawnOffset.y * sinf(_rotRad);
    float offsetY = spawnOffset.x * sinf(_rotRad) + spawnOffset.y * cosf(_rotRad);

    pos_.x += offsetX;
    pos_.y += offsetY;

    maxLinVel_ = 600.;
    linAcc_ = 200.;

    radius_ = 5;
    spriteInit(texture);
}

void Bullet::update(float deltaTime) {
    mainSprite_.setPosition(pos_);
    mainSprite_.setRotation(rot_);
    calculateLinVel(deltaTime);
}

void Bullet::draw(sf::RenderWindow &window) const {  window.draw(mainSprite_); }

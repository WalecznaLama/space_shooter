#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& position, const sf::Texture& texture, const float& angle) {
    sprite_.setTexture(texture);
    collisionRadius_ = 5;

    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
    sprite_.setPosition(position);

    initAngle_ = angle;
    sprite_.setRotation(initAngle_);
}

void Bullet::update(const float &velocity) {
    float _angle_rad = initAngle_ * (M_PI / 180.);
    float _dx = velocity * sinf(_angle_rad);
    float _dy = velocity * -cosf(_angle_rad);

    sprite_.move(_dx, _dy);
}

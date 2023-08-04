#include "Bullet.h"

Bullet::Bullet(const sf::Vector2u& windowSize, const sf::Vector2f& position, const sf::Texture& texture, const float& angle) {
    sprite_.setTexture(texture);

    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
    sprite_.setPosition(position);

    initAngle_ = angle;
    sprite_.setRotation(initAngle_);
    windowSize_ = windowSize;
}

void Bullet::update(const float &speed) {
    float _angle_rad = initAngle_ * (M_PI / 180.);
    float _dx = speed * sinf(_angle_rad);
    float _dy = speed * cosf(_angle_rad);

    sprite_.move(-_dx, _dy);
}



#include "Bullet.h"

Bullet::Bullet(const sf::Vector2u& windowSize, const sf::Vector2f& position, const sf::Texture& texture, const float& angle) {
    sprite_.setTexture(texture);

    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
    sprite_.setPosition(position);

    init_angle_ = angle;
    sprite_.setRotation(init_angle_);
    windowSize_ = windowSize;
}

void Bullet::update(const float &speed) {
    float angle_rad = init_angle_ * (M_PI / 180.);
    float dx = speed * sinf(angle_rad);
    float dy = speed * cosf(angle_rad);

    sprite_.move(-dx, dy);
}



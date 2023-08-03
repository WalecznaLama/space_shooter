#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& position, const sf::Texture& texture, const float& angle) {
    sprite_.setTexture(texture);
    sprite_.setPosition(position);
    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);

    init_angle_ = angle;
}

void Bullet::update(const float &speed) {
    float angle_rad = init_angle_ * (M_PI / 180.);
    float dx = speed * sinf(angle_rad);
    float dy = speed * cosf(angle_rad);

    sprite_.move(-dx, dy);
    sprite_.setRotation(init_angle_);
}
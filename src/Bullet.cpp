#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& position, const sf::Texture& texture, const float& angle) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

    init_angle = angle;
}

void Bullet::update(const float &speed) {
    float angle_rad = init_angle * (M_PI / 180.);
    float dx = speed * sinf(angle_rad);
    float dy = speed * cosf(angle_rad);

    sprite.move(-dx, dy);
    sprite.setRotation(init_angle);
}
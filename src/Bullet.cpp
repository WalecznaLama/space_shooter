#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& position, const sf::Texture& texture) {
    sprite.setTexture(texture);

    sf::Vector2f new_position = position;
    new_position.x -= texture.getSize().x / 2.;

    sprite.setPosition(new_position);
}

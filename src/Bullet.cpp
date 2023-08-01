#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& position, const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

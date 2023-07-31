#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& position, const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    texture_size = texture.getSize();  // save texture size

}

void Bullet::update(float dy) {
    sprite.move(0, dy);
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::Vector2f Bullet::getPosition() {
    sf::Vector2f position = sprite.getPosition();
    return {position.x + texture_size.x / 2, position.y + texture_size.y / 2};
}

const sf::Sprite &Bullet::getSprite() const {
    return sprite;
}

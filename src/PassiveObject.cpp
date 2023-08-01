#include "PassiveObject.h"

void PassiveObject::update(float dy) {
    sprite.move(0, dy);
}

void PassiveObject::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::Vector2f PassiveObject::getPosition() {
    sf::Vector2f position = sprite.getPosition();
    sf::Vector2u texture_size = sprite.getTexture()->getSize();
    return {position.x + texture_size.x / 2.f, position.y + texture_size.y / 2.f};
}

const sf::Sprite &PassiveObject::getSprite() const {
    return sprite;
}
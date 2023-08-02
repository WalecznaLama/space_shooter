#include "PassiveObject.h"

void PassiveObject::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::Vector2f PassiveObject::getPosition() {
    return sprite.getPosition();
}

const sf::Sprite &PassiveObject::getSprite() const {
    return sprite;
}
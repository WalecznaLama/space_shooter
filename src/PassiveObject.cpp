#include "PassiveObject.h"

void PassiveObject::draw(sf::RenderWindow& window) const {
    window.draw(sprite_);
}

sf::Vector2f PassiveObject::getPosition() {
    return sprite_.getPosition();
}

const sf::Sprite &PassiveObject::getSprite() const {
    return sprite_;
}
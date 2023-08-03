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

bool PassiveObject::isOffScreen() {
    sf::Vector2f position = getPosition();
    sf::Vector2u size = sprite_.getTexture()->getSize();
    sf::Vector2f half_size = sf::Vector2f(size.x/2., size.y/2.);

    if (position.y < 0) return true;
    if (position.y > windowSize_.y - half_size.y) return true;

    if (position.x < half_size.x) return true;
    if (position.x > windowSize_.x - half_size.x) return true;

    return false;
}
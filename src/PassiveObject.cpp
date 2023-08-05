#include "PassiveObject.h"

sf::Vector2f PassiveObject::getPosition() const { return sprite_.getPosition(); }

sf::FloatRect PassiveObject::getBounds() const { sprite_.getGlobalBounds(); }

void PassiveObject::setIsAlive(bool alive) { alive_ = alive; }

bool PassiveObject::getIsAlive() const { return alive_; }

void PassiveObject::draw(sf::RenderWindow& window) const { window.draw(sprite_); }

#include "SpaceObject.h"

const float SpaceObject::G_ = 1.0;

SpaceObject::SpaceObject (const sf::Texture &texture, const sf::Vector2f& initPosition,
                          const sf::Vector2f& initVelocity, const float initRotation,
                          const float radius, const float density)
        : position_(initPosition), velocity_(initVelocity),
        rotation_(initRotation), collisionRadius_(radius), density_(density) {
    mainSprite_.setTexture(texture);
    calculateGravity();
}

// Dla velocity_
void SpaceObject::setVelocity(const sf::Vector2f& velocity) { velocity_ = velocity; }
sf::Vector2f SpaceObject::getVelocity() const { return velocity_; }

// Dla position_
void SpaceObject::setPosition(const sf::Vector2f& position) { position_ = position; }
sf::Vector2f SpaceObject::getPosition() const { return position_; }

// Dla rotation_
void SpaceObject::setRotation(float rotation) { rotation_ = rotation; }
float SpaceObject::getRotation() const { return rotation_; }

// Dla collisionRadius_
void SpaceObject::setCollisionRadius(float collisionRadius) { collisionRadius_ = collisionRadius; }
float SpaceObject::getCollisionRadius() const { return collisionRadius_; }

float SpaceObject::getGravity() const { return gravity_; }

const sf::Sprite &SpaceObject::getSprite() const { return mainSprite_; }

void SpaceObject::scaleSprite(const sf::Vector2f &factor) { mainSprite_.scale(factor); }
void SpaceObject::scaleSprite(const float factorX, const float factorY) { mainSprite_.scale(factorX, factorY); }

void SpaceObject::calculateGravity() {
    gravity_ = (G_ * density_ * std::pow(collisionRadius_, 3)) / std::pow(collisionRadius_, 2);
}

void SpaceObject::update() {
    mainSprite_.setPosition(position_);
    mainSprite_.setRotation(rotation_);
}


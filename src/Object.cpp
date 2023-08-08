#include "Object.h"

void Object::setPosition(const sf::Vector2f& newPosition) { position_ = newPosition; }
sf::Vector2f Object::getPosition() const { return position_; }

void Object::setRotation(float newRotation) { rotation_ = newRotation; }
float Object::getRotation() const { return rotation_; }

void Object::setLinearVelocity(const sf::Vector2f& velocity) { linVel_ = velocity; }
sf::Vector2f Object::getLinearVelocity() const { return linVel_; }

void Object::setAngularVelocity(float newVelocity) { angVel_ = newVelocity; }
float Object::getAngularVelocity() const { return angVel_; }

void Object::setRadius(float collisionRadius) { radius_ = collisionRadius; }
float Object::getRadius() const { return radius_; }

void Object::setIsAlive(bool isAlive) { alive_ = isAlive; }
bool Object::getIsAlive() const { return alive_; }

sf::FloatRect Object::getBounds() const { return mainSprite_.getGlobalBounds(); }

void Object::addSprite(const std::string& sprite_name, const sf::Texture& texture) {
    sprites_[sprite_name] = sf::Sprite(texture);
    sprites_[sprite_name].setOrigin(sprites_[sprite_name].getLocalBounds().width / 2,
                                    sprites_[sprite_name].getLocalBounds().height / 2);
}

const sf::Sprite &Object::getSprite() const { return mainSprite_; }

float Object::vectorLength(const sf::Vector2f& vec) { return std::sqrt(vec.x * vec.x + vec.y * vec.y); }

sf::Vector2f Object::vectorNormalize(const sf::Vector2f& vector) {
    float len = vectorLength(vector);
    if (len != 0)   return sf::Vector2f(vector.x / len, vector.y / len);
    else            return sf::Vector2f(0.f, 0.f);
}

sf::Vector2f Object::calculateLinAccDirection() const {
    return sf::Vector2f(sinf(rotation_ * M_PI / 180.0f), -cosf(rotation_ * M_PI / 180.0f));
}

/// acceleration 0-1
sf::Vector2f Object::calculateAcceleration(sf::Vector2f accelerationDirection, float deltaTime) const {
    float actualAcceleration = linAcc_  / mass_;
    return accelerationDirection * actualAcceleration * deltaTime;
}

void Object::scaleSprite(sf::Sprite &sprite, const sf::Vector2f &factor) { sprite.scale(factor); }
void Object::scaleSprite(sf::Sprite &sprite, float factorX, float factorY) {sprite.scale(factorX, factorY); }

void Object::spriteInit(const std::map<std::string, sf::Texture> &textures) {
    for (const auto& texturePair : textures)   addSprite(texturePair.first, texturePair.second);
    mainSprite_ = sprites_["main"];
    updateMainSpritePosition();
}
void Object::spriteInit(const sf::Texture &texture) {
    addSprite("main", texture);
    mainSprite_ = sprites_["main"];
    updateMainSpritePosition();
}

float Object::getMass() const { return mass_; }

void Object::calculateLinearVelocity(float deltaTime) {

    calculateAngularVelocity(deltaTime);

    sf::Vector2f _linAccDirection = calculateLinAccDirection();
    sf::Vector2f _deltaLinAccForce = calculateAcceleration(_linAccDirection, deltaTime); // force from space engine

    linVel_ += _deltaLinAccForce;
    if (vectorLength(linVel_) > maxLinVel_) linVel_ = vectorNormalize(linVel_) * maxLinVel_;
}

void Object::calculateAngularVelocity(float deltaTime) {
    angVel_ += (angAcc_ * deltaTime);
    angVel_ = std::clamp(angVel_, -maxAngVel_, maxAngVel_);
}

void Object::updateMainSpritePosition() {
    mainSprite_.setPosition(position_);
    mainSprite_.setRotation(rotation_);
}

void Object::setLinearAcceleration(float newAcc) { linAcc_ = newAcc; }
float Object::getLinearAcceleration() const { return linAcc_; }

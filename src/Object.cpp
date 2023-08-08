#include "Object.h"

void Object::setPosition(const sf::Vector2f& newPosition) { position_ = newPosition; }
sf::Vector2f Object::getPosition() const { return position_; }

void Object::setRotation(float newRotation) { rotation_ = newRotation; }
float Object::getRotation() const { return rotation_; }

void Object::setLinearVelocity(const sf::Vector2f& velocity) { linVel_ = velocity; }
sf::Vector2f Object::getLinearVelocity() const { return linVel_; }

void Object::setAngularVelocity(float newVelocity) { angVel_ = newVelocity; }
float Object::getAngularVelocity() const { return angVel_; }

void Object::setAngularAcceleration(float newAcceleration) { angAcc_ = newAcceleration; }
float Object::getAngularAcceleration() const { return angAcc_; }

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

sf::Vector2f Object::calculateLinearAcceleration(sf::Vector2f accelerationDirection, float deltaTime) const {
    return accelerationDirection * linAcc_ * deltaTime;
}

void Object::scaleSprite(sf::Sprite &sprite, const sf::Vector2f &factor) { sprite.scale(factor); }
void Object::scaleSprite(sf::Sprite &sprite, float factorX, float factorY) {sprite.scale(factorX, factorY); }

void Object::spriteInit(const std::map<std::string, sf::Texture> &textures) {
    for (const auto& texturePair : textures)   addSprite(texturePair.first, texturePair.second);
    mainSprite_ = sprites_["main"];
    mainSprite_.setPosition(position_);
    mainSprite_.setRotation(rotation_);
}
void Object::spriteInit(const sf::Texture &texture) {
    addSprite("main", texture);
    mainSprite_ = sprites_["main"];
    mainSprite_.setPosition(position_);
    mainSprite_.setRotation(rotation_);
}

sf::Vector2f Object::calculateLinearAccDirection() const {
    return sf::Vector2f(sinf(rotation_ * M_PI / 180.0f), -cosf(rotation_ * M_PI / 180.0f));
}

void Object::calculateLinearVelocity(float deltaTime) {
    sf::Vector2f _linAccDirection = calculateLinearAccDirection();
    sf::Vector2f _deltaLinAcc = calculateLinearAcceleration(_linAccDirection, deltaTime); // force from space engine

    linVel_ += _deltaLinAcc;
    if (vectorLength(linVel_) > maxLinVel_) linVel_ = vectorNormalize(linVel_) * maxLinVel_;
}

void Object::calculateAngularVelocity(float deltaTime) {
    angVel_ += (angAcc_ * deltaTime);
    angVel_ = std::clamp(angVel_, -maxAngVel_, maxAngVel_);
}


void Object::setLinearAcceleration(float newAcc) { linAcc_ = newAcc; }
float Object::getLinearAcceleration() const { return linAcc_; }

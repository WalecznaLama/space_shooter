#include "Object.h"

void Object::setPos(const sf::Vector2f& newPos) { pos_ = newPos; }
sf::Vector2f Object::getPos() const { return pos_; }

void Object::setRot(float newRot) { rot_ = newRot; }
float Object::getRot() const { return rot_; }

void Object::setLinVel(const sf::Vector2f& vel) { linVel_ = vel; }
sf::Vector2f Object::getLinVel() const { return linVel_; }

void Object::setAngVel(float newVel) { angVel_ = newVel; }
float Object::getAngVel() const { return angVel_; }

void Object::setAngAcc(float newAcc) { angAcc_ = newAcc; }
float Object::getAngAcc() const { return angAcc_; }

void Object::setRadius(int collisionRadius) { radius_ = collisionRadius; }
int Object::getRadius() const { return radius_; }

void Object::setIsAlive(bool isAlive) { alive_ = isAlive; }
bool Object::getIsAlive() const { return alive_; }

void Object::setBounds(sf::FloatRect bounds) { bounds_ = bounds; }
sf::FloatRect Object::getBounds() const { return bounds_; }

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

sf::Vector2f Object::calculateLinAcc(sf::Vector2f accDirection, float deltaTime) const {
    return accDirection * linAcc_ * deltaTime;
}

void Object::scaleSprite(sf::Sprite &sprite, const sf::Vector2f &factor) { sprite.scale(factor); }
void Object::scaleSprite(sf::Sprite &sprite, float factorX, float factorY) {sprite.scale(factorX, factorY); }

void Object::spriteInit(const std::map<std::string, sf::Texture> &textures) {
    for (const auto& texturePair : textures)   addSprite(texturePair.first, texturePair.second);
    mainSprite_ = sprites_["main"];
    mainSprite_.setPosition(pos_);
    mainSprite_.setRotation(rot_);
}
void Object::spriteInit(const sf::Texture &texture) {
    addSprite("main", texture);
    mainSprite_ = sprites_["main"];
    mainSprite_.setPosition(pos_);
    mainSprite_.setRotation(rot_);
}

sf::Vector2f Object::calculateLinAccDirection() const {
    return sf::Vector2f(sinf(rot_ * M_PI / 180.0f), -cosf(rot_ * M_PI / 180.0f));
}

void Object::calculateLinVel(float deltaTime) {
    sf::Vector2f _linAccDirection = calculateLinAccDirection();
    linVel_ += calculateLinAcc(_linAccDirection, deltaTime); // force from space engine;
    if (vectorLength(linVel_) > maxLinVel_) linVel_ = vectorNormalize(linVel_) * maxLinVel_;
}

void Object::calculateAngVel(float deltaTime) {
    angVel_ += (angAcc_ * deltaTime);
    angVel_ = std::clamp(angVel_, -maxAngVel_, maxAngVel_);
}


void Object::setLinAcc(float newAcc) { linAcc_ = newAcc; }
float Object::getLinAcc() const { return linAcc_; }

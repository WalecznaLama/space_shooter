#include "Entity.h"

bool Entity::canShoot(float time_to_shoot){
    sf::Time elapsed = shootClock_.getElapsedTime();
    float interval;

    if (!firstShotFired_)  interval = time_to_shoot / 10.f;
    else    interval = time_to_shoot;

    if (elapsed.asSeconds() >= interval) {
        shootClock_.restart();
        firstShotFired_ = true;
        return true;
    }
    return false;
}

void Entity::addSprite(const std::string& sprite_name, const sf::Texture& texture) {
    sprites_[sprite_name] = sf::Sprite(texture);
    sprites_[sprite_name].setOrigin(sprites_[sprite_name].getLocalBounds().width / 2,
                                    sprites_[sprite_name].getLocalBounds().height / 2);
}

float Entity::vectorLength(const sf::Vector2f& vec) { return std::sqrt(vec.x * vec.x + vec.y * vec.y); }

sf::Vector2f Entity::vectorNormalize(const sf::Vector2f& vector) {
    float len = vectorLength(vector);
    if (len != 0)   return sf::Vector2f(vector.x / len, vector.y / len);
    else            return sf::Vector2f(0.f, 0.f);
}

sf::Vector2f Entity::calculateForceDirection() const {
    return sf::Vector2f(sinf(rotation_ * M_PI / 180.0f), -cosf(rotation_ * M_PI / 180.0f));
}

/// acceleration 0-1
sf::Vector2f Entity::calculateAcceleration(sf::Vector2f _engineForceDirection, float acceleration, float deltaTime) const {
    float actualAcceleration = (linAcc_ * acceleration) / mass_;
    return _engineForceDirection * actualAcceleration * deltaTime;
}

void Entity::draw(sf::RenderWindow& window) const{ window.draw(mainSprite_); }

sf::Vector2f Entity::getPosition() const{ return position_; }

float Entity::getRotation() const { return rotation_; }

const sf::Sprite& Entity::getSprite() const { return mainSprite_; }

bool Entity::getIsAlive() const { return alive_; }

sf::Vector2f Entity::getLinearVelocity() const { return velocity_; }

float Entity::getAngularVelocity() const { return angularVel_; }

sf::FloatRect Entity::getBounds() const { return mainSprite_.getGlobalBounds(); }

void Entity::setPosition(sf::Vector2f& newPosition) { position_ = newPosition; }

void Entity::setVelocity(sf::Vector2f &newVelocity) { velocity_ = newVelocity; }

void Entity::setRotation(float newRotation) { rotation_ = newRotation; }

float Entity::getRadius() const { return collisionRadius_; }

void Entity::setIsAlive(bool isAlive) { alive_ = isAlive; }

int Entity::getHp() const { return hp_; }

int Entity::getMaxHp() const { return maxHp_; }

void Entity::setDamage(int damage) { hp_ = std::max(0, hp_ - damage); }

float Entity::getMass() const { return mass_; }

sf::Vector2f Entity::getVelocity() const { return velocity_; }

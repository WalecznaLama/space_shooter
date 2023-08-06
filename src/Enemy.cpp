#include <cmath>
#include <utility>
#include "Enemy.h"

Enemy::Enemy(const sf::Vector2f spawn_point, const sf::Texture& texture) {
    collisionRadius_ = 40;
    linAcc_ = 20.;
    maxLinearVel_ = 30.;
    maxAngularVel_ = 150.;
    angAcc_ = 200.;
    position_ = spawn_point;
    init(texture);

    mass_ = 1.0;
    maxHp_ = 2.;

    hp_ = maxHp_;
}

void Enemy::init(const sf::Texture& texture) {
    addSprite("main", texture);
    mainSprite_ = sprites_["main"];
    mainSprite_.setOrigin(mainSprite_.getLocalBounds().width / 2, mainSprite_.getLocalBounds().height / 2);
    mainSprite_.setPosition(position_);
}

void Enemy::update(const sf::Vector2f& playerPosition, float deltaTime) {
    sf::Vector2f direction = playerPosition - position_; // Compute direction from enemy to player
    float targetAngle = std::atan2(direction.y, direction.x); // Compute angle to player
    targetAngle = targetAngle * 180 / M_PI + 90; // Convert to degrees and adjust for SFML's coordinate system

    float currentAngle = rotation_; // Get enemy's current rotation
    if (targetAngle < 0) targetAngle += 360;
    if (currentAngle < 0) currentAngle += 360;
    float angleDifference = std::fmod(targetAngle - currentAngle, 360);

    // Normalize the direction vector (make it have a length of 1)
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//    sf::Vector2f normalizedDirection = direction / length;

    calculateVelocity(length, angleDifference, deltaTime);
    if (vectorLength(velocity_) > maxLinearVel_) velocity_ = vectorNormalize(velocity_) * maxLinearVel_;

    mainSprite_.setPosition(position_);
    mainSprite_.setRotation(rotation_);

    if (hp_ == 0) setIsAlive(false);
}

void Enemy::calculateVelocity(const float& lin_acc, const float& theta_acc, const float& deltaTime) {
    calculateAngularVelocity(theta_acc, deltaTime);

    sf::Vector2f _engineForceDirection = calculateForceDirection();
    sf::Vector2f _acceleration = calculateAcceleration(_engineForceDirection,
                                                       lin_acc, deltaTime);
    velocity_ += _acceleration;
}

void Enemy::calculateAngularVelocity(float theta_acc, float deltaTime) {
    angularVel_ += (angAcc_ * deltaTime * theta_acc);
    angularVel_ = std::clamp(angularVel_, -maxAngularVel_, maxAngularVel_);
}

bool Enemy::getIsKilledByPlayer() const { return killedByBullet_; }

void Enemy::setIsKilledByPlayer(bool isKilledByPlayer) { killedByBullet_ = isKilledByPlayer; }

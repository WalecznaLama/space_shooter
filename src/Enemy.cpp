#include "Enemy.h"


Enemy::Enemy(sf::Vector2f spawn_point, const sf::Texture& texture) :
        pidController_(5.0, 2.0, 0.0, maxAngAcc_)
{
    position_ = spawn_point;

    radius_ = 10;
    linAcc_ = 100.;
    maxLinVel_ = 200.;
    maxAngVel_ = 50.;
    maxAngAcc_ = 300.;

    mass_ = 1.0;

    maxHp_ = 2;
    hp_ = maxHp_;

    spriteInit(texture);
}

void Enemy::update(const sf::Vector2f& playerPosition, float deltaTime) {
    mainSprite_.setPosition(position_);
    mainSprite_.setRotation(rotation_);

    sf::Vector2f direction = playerPosition - position_; // Compute direction from enemy to player
    float targetAngle = std::atan2(direction.y, direction.x); // Compute angle to player
    targetAngle = targetAngle * 180 / M_PI + 90; // Convert to degrees and adjust for SFML's coordinate system

    float currentAngle = rotation_; // Get enemy's current rotation
    if (targetAngle < 0) targetAngle += 360;
    if (currentAngle < 0) currentAngle += 360;

    // Oblicz różnicę kątów, znormalizowaną do zakresu -180 do 180
    float angleDifference = std::fmod(targetAngle - currentAngle, 360.0f);
    if (angleDifference > 180.0f) angleDifference -= 360.0f;
    if (angleDifference < -180.0f) angleDifference += 360.0f;

    angAcc_ = pidController_.pidOutput(angleDifference, deltaTime);
    calculateAngularVelocity(deltaTime);

    calculateLinearVelocity(deltaTime);

    if (hp_ == 0) setIsAlive(false);
}

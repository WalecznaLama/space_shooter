#include <cmath>
#include <utility>
#include "Enemy.h"

Enemy::Enemy(const sf::Vector2u& windowSize, const sf::Texture& texture){
    windowSize_ = windowSize;
    init(texture);

    linAcc_ = 20.;
    maxLinearVel_ = 30.;
    maxAngularVel_ = 150.;
    angAcc_ = 200.;
}

void Enemy::init(const sf::Texture& texture) {
    addSprite("main", texture);
    mainSprite_ = sprites_["main"];

    std::random_device rd;  // (seed)
    std::mt19937 gen(rd());  // generator liczb pseudolosowych
    std::uniform_int_distribution<> distr(0, 3);  // rozkład jednostajny

    int _spawnDirection = distr(gen);  // 0 - Up, 1 - Right, 2 - Down, 3 - Left
    float _x, _y;
    switch (_spawnDirection) {
        case Direction::Up:
            _x = (float)(std::rand() % windowSize_.x);
            _y = 0;
            break;
        case Direction::Down:
            _x = (float)(std::rand() % windowSize_.x);
            _y = windowSize_.y - mainSprite_.getLocalBounds().height;
            break;
        case Direction::Left:
            _x = 0;
            _y = (float)(std::rand() % windowSize_.y);
            break;
        case Direction::Right:
            _x = windowSize_.x - mainSprite_.getLocalBounds().width;
            _y = (float)(std::rand() % windowSize_.y);
            break;
    }
    position_ = {_x, _y};
    mainSprite_.setOrigin(mainSprite_.getLocalBounds().width / 2, mainSprite_.getLocalBounds().height / 2);
    mainSprite_.setPosition(position_);
}

void Enemy::update(std::vector <Bullet> &bullets, const sf::Vector2f& playerPosition) {
    const auto &elapsed = updateClock_.getElapsedTime().asSeconds();
    updateClock_.restart();

    sf::Vector2f direction = playerPosition - position_; // Compute direction from enemy to player
    float targetAngle = std::atan2(direction.y, direction.x); // Compute angle to player
    targetAngle = targetAngle * 180 / M_PI + 90; // Convert to degrees and adjust for SFML's coordinate system

    float currentAngle = rotation_; // Get enemy's current rotation
    float angleDifference = targetAngle - currentAngle; // Compute absolute difference
//    if (angleDifference > 180.)  angleDifference = 360. - angleDifference;


    // Normalize the direction vector (make it have a length of 1)
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//    sf::Vector2f normalizedDirection = direction / length;

    // TODO
    calculateVelocity(-length, angleDifference, elapsed);
    if (vectorLength(velocity_) > maxLinearVel_) velocity_ = vectorNormalize(velocity_) * maxLinearVel_;

    position_ += velocity_ * elapsed;
    rotation_ += angularVel_ * elapsed;

    mainSprite_.setPosition(position_);
    mainSprite_.setRotation(rotation_);

    checkBulletsCollision(bullets);
    if (mainSprite_.getPosition().y > windowSize_.y) alive_ = false;
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

bool Enemy::isKilledByPlayer() { return killedByBullet_; }


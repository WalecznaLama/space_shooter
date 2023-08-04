#include <cmath>
#include "Enemy.h"

Enemy::Enemy(const sf::Vector2u& windowSize, const sf::Texture& texture) {
    windowSize_ = windowSize;
    init(texture);
}

void Enemy::init(const sf::Texture& texture) {
    addSprite("main", texture);
    mainSprite_ = sprites_["main"];

    // set initial position at a random position at the top of the screen
    std::srand(std::time(nullptr));
    auto x = (float)(std::rand() % windowSize_.x);
    mainSprite_.setPosition(x, 0);
    mainSprite_.setOrigin(mainSprite_.getLocalBounds().width / 2, mainSprite_.getLocalBounds().height / 2);
    acceleration_ = 0.001;
    maxTilt_ = 40;
}

void Enemy::update(const sf::Vector2f& speed, std::vector <Bullet> &bullets) {
    const auto &elapsed = updateClock_.getElapsedTime().asMilliseconds();
    updateClock_.restart();
    float error = playerPosition_.x - mainSprite_.getPosition().x;
    float finat_dx = 0;
    float angle = error * speed.x * elapsed * acceleration_;

    if (error > windowSize_.x / 20 or error < -windowSize_.x / 20)      finat_dx = angle;

    finat_dx = std::clamp(finat_dx, -speed.x, speed.x);

    float rotate = (finat_dx / speed.x) * -maxTilt_;
    mainSprite_.move(finat_dx, speed.y);
    mainSprite_.setRotation(rotate);
    checkBulletsCollision(bullets);
    if (mainSprite_.getPosition().y > windowSize_.y) alive_ = false;
}

bool Enemy::isKilledByPlayer() { return killedByBullet_; }

void Enemy::setPlayerPosition(const sf::Vector2f &playerPosition) { playerPosition_ = playerPosition; }

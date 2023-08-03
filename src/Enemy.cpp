#include <cmath>
#include "Enemy.h"

Enemy::Enemy(const sf::Vector2u& windowSize, const sf::Texture& texture) {
    init(windowSize, texture);
}

void Enemy::init(const sf::Vector2u &windowSize, const sf::Texture &texture) {
    addTexture("main", texture);
    sprite_.setTexture(textures_["main"]);

    windowSize_ = windowSize;
    // set initial position at a random position at the top of the screen
    std::srand(std::time(nullptr));
    auto x = (float)(std::rand() % windowSize_.x);
    sprite_.setPosition(x, 0);
    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
    acceleration_ = 0.001;
}


void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(sprite_);
}

void Enemy::update(const sf::Vector2f& speed, std::vector <Bullet> &bullets) {
    const auto &elapsed = updateClock_.getElapsedTime().asMilliseconds();
    updateClock_.restart();
    float error = playerPosition_.x - sprite_.getPosition().x;
    float finat_dx = 0;
    float angle = error * speed.x * elapsed * acceleration_;

    if(error > windowSize_.x / 20 or error < -windowSize_.x / 20)      finat_dx = angle;

    finat_dx = std::clamp(finat_dx, -speed.x, speed.x);

    float rotate = (finat_dx / speed.x) * -30;
    sprite_.move(finat_dx, speed.y);
    sprite_.setRotation(rotate);
    checkBulletsCollision(bullets);
    if (sprite_.getPosition().y > windowSize_.y) alive_ = false;
}

bool Enemy::isKilledByPlayer() {
    return killed_by_bullet_;
}

void Enemy::setPlayerPosition(const sf::Vector2f &playerPosition) {
    playerPosition_ = playerPosition;
}


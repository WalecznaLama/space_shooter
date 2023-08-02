#include <cmath>
#include "Enemy.h"

Enemy::Enemy(const sf::Vector2u& windowSize, const sf::Texture& texture) {
    sprite.setTexture(texture);

    // set initial position at a random position at the top of the screen
    std::srand(std::time(nullptr));
    auto x = (float)(std::rand() % windowSize.x);
    sprite.setPosition(x, 0);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Enemy::update(float dx, float dy, sf::Vector2f player_position) {
    float error = player_position.x - sprite.getPosition().x;
    float finat_dx = 0;
    float angle = error * dx * 0.004;

    if(error > 10 or error < -10)      finat_dx = angle;

    finat_dx = std::clamp(finat_dx, -dx, dx);

    float rotate = (finat_dx / dx) * -30;
    sprite.move(finat_dx, dy);
    sprite.setRotation(rotate);
}

sf::Vector2f Enemy::getPosition() {
    return sprite.getPosition();
}

bool Enemy::canShoot(float time_to_shoot) {
    sf::Time elapsed = shootClock.getElapsedTime();
    float interval;

    if (!first_shot_fired) {
        interval = time_to_shoot / 10.f;
    } else {
        interval = time_to_shoot;
    }

    if (elapsed.asSeconds() >= interval) {
        shootClock.restart();
        first_shot_fired = true;
        return true;
    }
    return false;
}

const sf::Sprite &Enemy::getSprite() const {
    return sprite;
}

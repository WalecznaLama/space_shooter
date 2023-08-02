#include <cmath>
#include "Enemy.h"

Enemy::Enemy(const sf::Vector2u& windowSize, const sf::Texture& texture) {
    sprite.setTexture(texture);

    window_size = windowSize;
    // set initial position at a random position at the top of the screen
    std::srand(std::time(nullptr));
    auto x = (float)(std::rand() % window_size.x);
    sprite.setPosition(x, 0);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Enemy::update(float dx, float dy, sf::Vector2f player_position,
                   std::vector<Bullet>& playerBullets) {
    float error = player_position.x - sprite.getPosition().x;
    float finat_dx = 0;
    float angle = error * dx * 0.004;

    if(error > 10 or error < -10)      finat_dx = angle;

    finat_dx = std::clamp(finat_dx, -dx, dx);

    float rotate = (finat_dx / dx) * -30;
    sprite.move(finat_dx, dy);
    sprite.setRotation(rotate);

    for (int j = playerBullets.size() - 1; j >= 0; --j) {
        if (sprite.getGlobalBounds().intersects(playerBullets[j].getSprite().getGlobalBounds())) {
            alive = false;
            killed_by_player = true;
            playerBullets.erase(playerBullets.begin() + j);
            break;
        }
    }

    if (sprite.getPosition().y > window_size.y){
        alive = false;
    }
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

bool Enemy::isAlive() {
    return alive;
}

bool Enemy::isKilledByPlayer() {
    return killed_by_player;
}

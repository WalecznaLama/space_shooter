#include "Enemy.h"

Enemy::Enemy(const sf::Vector2u& windowSize, const sf::Texture& texture) {
    sprite.setTexture(texture);

    // set initial position at a random position at the top of the screen
    std::srand(std::time(nullptr));
    auto x = (float)(std::rand() % windowSize.x);
    sprite.setPosition(x, 0);

}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Enemy::update(float speed) {
    sprite.move(0, speed);
}

sf::Vector2f Enemy::getPosition() {
    sf::Vector2f position = sprite.getPosition();
    sf::Vector2u texture_size = sprite.getTexture()->getSize();
    return {position.x + texture_size.x / 2.f, position.y + texture_size.y / 2.f};
}

bool Enemy::canShoot(float time_to_shoot) {
    sf::Time elapsed = shootClock.getElapsedTime();
    float interval;

    if (!first_shot_fired) {
        interval = time_to_shoot / 10.f;  // shoot after 0.2 seconds when the enemy spawns
    } else {
        interval = time_to_shoot;  // afterward, shoot every 2 seconds
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

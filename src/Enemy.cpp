#include "Enemy.h"

Enemy::Enemy(const sf::Vector2u& windowSize, const sf::Texture& texture) {

    sprite.setTexture(texture);

    // set initial position at a random position at the top of the screen
    auto x = (float)(rand() % windowSize.x);
    sprite.setPosition(x, 0);
    texture_size = texture.getSize();  // save texture size
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Enemy::update() {
    float speed = 0.3f;  // adjust as needed
    sprite.move(0, speed);
}

sf::Vector2f Enemy::getPosition() {
    sf::Vector2f position = sprite.getPosition();
    return {position.x + texture_size.x / 2, position.y + texture_size.y / 2};
}

bool Enemy::canShoot() {
    sf::Time elapsed = shootClock.getElapsedTime();
    if (elapsed.asSeconds() >= 3.0f) {  // shoot every 3 seconds
        shootClock.restart();
        return true;
    }
    return false;
}

const sf::Sprite &Enemy::getSprite() const {
    return sprite;
}

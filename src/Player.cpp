#include "Player.h"

Player::Player() = default;

void Player::init(const sf::Vector2u& windowSize, const sf::Texture& texture) {

    sprite.setTexture(texture);

    // set initial position at the bottom of the screen
    float x = windowSize.x / 2. - texture.getSize().x / 2.;
    float y = windowSize.y - texture.getSize().y;

    sprite.setPosition(x, y);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    acceleration = 30;
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Player::update(const sf::Vector2u& windowSize,const sf::Vector2f& speed,
                    const std::vector<Enemy>& enemies, const std::vector<Bullet>& enemyBullets) {
    sf::Time elapsed = updateClock.getElapsedTime();
    updateClock.restart();

    userMovement(speed, elapsed);

    // keep the player inside the screen bounds
    sf::Vector2f position = sprite.getPosition();
    sf::Vector2u size = sprite.getTexture()->getSize();
    sf::Vector2f half_size = sf::Vector2f(size.x/2., size.y/2.);

    if (position.x < half_size.x) position.x = half_size.x;
    if (position.y < half_size.y) position.y = half_size.y;
    if (position.x > windowSize.x - half_size.x) position.x = windowSize.x - half_size.x;
    if (position.y > windowSize.y - half_size.y) position.y = windowSize.y - half_size.y;

    sprite.setPosition(position);
    checkPlayerCollision(enemies, enemyBullets);
}

sf::Vector2f Player::getPosition() {
    return sprite.getPosition();
}

bool Player::canShoot(float time_to_shoot) {
    sf::Time elapsed = shootClock.getElapsedTime();
    if (elapsed.asSeconds() >= time_to_shoot) {  // shoot every 0.5 seconds
        shootClock.restart();
        return true;
    }
    return false;
}

const sf::Sprite &Player::getSprite() const {
    return sprite;
}

void Player::checkPlayerCollision(const std::vector<Enemy>& enemies, const std::vector<Bullet>& enemyBullets) {
    sf::FloatRect playerBounds = sprite.getGlobalBounds();

    for (const auto& enemy : enemies) {
        sf::FloatRect enemyBounds = enemy.getSprite().getGlobalBounds();

        if (playerBounds.intersects(enemyBounds)) {
            // Player and enemy have collided
            alive = false;
            return;
        }
    }

    for (const auto& bullet : enemyBullets) {
        sf::FloatRect bulletBounds = bullet.getSprite().getGlobalBounds();

        if (playerBounds.intersects(bulletBounds)) {
            // Player and bullet have collided
            alive = false;
            return;
        }
    }

}

void Player::userMovement(const sf::Vector2f& speed, sf::Time elapsed) {
    sf::Vector2f movement(0.f, 0.f);
    float rotation_degrees = 30;
    float rotation = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        current_speed.x -= speed.x / elapsed.asMicroseconds() * acceleration;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        current_speed.x += speed.x / elapsed.asMicroseconds() * acceleration;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        current_speed.y -= speed.y / elapsed.asMicroseconds() * acceleration;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += speed.y;
        current_speed.y += speed.y / elapsed.asMicroseconds() * acceleration;
        rotation *= -1.;
    }
    current_speed.x = std::clamp(current_speed.x, -speed.x, speed.x);
    current_speed.y = std::clamp(current_speed.y, -speed.y, speed.y);

    movement = sf::Vector2f(current_speed);
    rotation = (current_speed.x / speed.x) * rotation_degrees;

    // apply the movement
    sprite.move(movement);
    sprite.setRotation(rotation);
}

bool Player::isALive() {
    return alive;
}

void Player::setRotationAcceleration(float rotationAcceleration) {
    acceleration = rotationAcceleration;
}

float Player::getRotationAcceleration() const {
    return acceleration;
}

void Player::multiplyRotationAcceleration(float k) {
    acceleration *= k;
}

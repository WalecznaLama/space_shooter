#include "Player.h"

Player::Player() = default;

void Player::init(const sf::Vector2u& windowSize, const sf::Texture& texture) {

    sprite.setTexture(texture);

    // set initial position at the bottom of the screen
    float x = windowSize.x / 2 - texture.getSize().x / 2;
    float y = windowSize.y - texture.getSize().y;
    sprite.setPosition(x, y);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Player::update(const sf::Vector2u& windowSize, const sf::Vector2f& speed) {
    sf::Vector2f movement(0.f, 0.f);
    float rotation_degrees = 10;
    float rotation = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement.x -= speed.x;
        rotation = -rotation_degrees;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += speed.x;
        rotation = rotation_degrees;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        movement.y -= speed.y;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += speed.y;
        rotation *= -1.;
    }

    // apply the movement
    sprite.move(movement);
    sprite.setRotation(rotation);

    // keep the player inside the screen bounds
    sf::Vector2f position = sprite.getPosition();
    sf::Vector2u size = sprite.getTexture()->getSize();

    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;

    if (position.x > windowSize.x - size.x) position.x = windowSize.x - size.x;
    if (position.y > windowSize.y - size.y) position.y = windowSize.y - size.y;

    sprite.setPosition(position);
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


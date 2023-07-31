#include "Player.h"

Player::Player() = default;

void Player::init(const sf::Vector2u& windowSize) {
    if (!texture.loadFromFile("resources/player.png")) {
        // handle error
    }
    sprite.setTexture(texture);

    // set initial position at the bottom of the screen
    float x = windowSize.x / 2 - texture.getSize().x / 2;
    float y = windowSize.y - texture.getSize().y;
    sprite.setPosition(x, y);
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Player::update(const sf::Vector2u& windowSize) {
    float speed = 0.02f; // adjust as needed

    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        movement.y -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement.x -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += speed;
    }

    // apply the movement
    sprite.move(movement);

    // keep the player inside the screen bounds
    sf::Vector2f position = sprite.getPosition();
    sf::Vector2u size = sprite.getTexture()->getSize();

    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;

    if (position.x > windowSize.x - size.x) position.x = windowSize.x - size.x;
    if (position.y > windowSize.y - size.y) position.y = windowSize.y - size.y;

    sprite.setPosition(position);
}


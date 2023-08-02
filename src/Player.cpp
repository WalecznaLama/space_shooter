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

void Player::update(const sf::Vector2u& windowSize,const sf::Vector2f& speed,
                    const std::vector<Enemy>& enemies, const std::vector<Bullet>& enemyBullets) {
    sf::Time elapsed = updateClock.getElapsedTime();
    updateClock.restart();

    userMovement(speed, elapsed);


    // keep the player inside the screen bounds
    sf::Vector2f position = sprite.getPosition();
    sf::Vector2u size = sprite.getTexture()->getSize();

    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;

    if (position.x > windowSize.x - size.x) position.x = windowSize.x - size.x;
    if (position.y > windowSize.y - size.y) position.y = windowSize.y - size.y;

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
    float dx_multipler = 30;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        current_dx -= speed.x/elapsed.asMicroseconds()*dx_multipler;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        current_dx += speed.x/elapsed.asMicroseconds()*dx_multipler;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        movement.y -= speed.y;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += speed.y;
        rotation *= -1.;
    }
    current_dx = std::clamp(current_dx, -speed.x, speed.x);
    movement.x = current_dx;
    rotation = (current_dx / speed.x) * rotation_degrees;

    // apply the movement
    sprite.move(movement);
    sprite.setRotation(rotation);
}

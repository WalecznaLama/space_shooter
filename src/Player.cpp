#include "Player.h"

Player::Player() = default;

void Player::init(const sf::Vector2u& windowSize, const sf::Texture& texture) {
    addTexture("engine_off", texture);
    sprite_.setTexture(textures_["engine_off"]);
    windowSize_ = windowSize;
    // set initial position at the bottom of the screen
    float x = windowSize.x / 2. - texture.getSize().x / 2.;
    float y = windowSize.y - texture.getSize().y;

    sprite_.setPosition(x, y);
    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
    acceleration_ = 30;
}

void Player::update(const sf::Vector2f& speed, std::vector<Bullet>& bullets) {
    sf::Time elapsed = updateClock_.getElapsedTime();
    updateClock_.restart();

    userMovement(speed, elapsed);

    // keep the player_ inside the screen bounds
    sf::Vector2f position = sprite_.getPosition();
    sf::Vector2u size = sprite_.getTexture()->getSize();
    sf::Vector2f half_size = sf::Vector2f(size.x/2., size.y/2.);

    if (position.x < half_size.x) position.x = half_size.x;
    if (position.y < half_size.y) position.y = half_size.y;
    if (position.x > windowSize_.x - half_size.x) position.x = windowSize_.x - half_size.x;
    if (position.y > windowSize_.y - half_size.y) position.y = windowSize_.y - half_size.y;

    sprite_.setPosition(position);
    checkBulletsCollision(bullets);
}

void Player::userMovement(const sf::Vector2f& speed, sf::Time elapsed) {
    sf::Vector2f movement(0.f, 0.f);
    float _rotation_degrees = 30;
    float _rotation = 0;
    bool _moved = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        currentSpeed_.x -= speed.x / elapsed.asMicroseconds() * acceleration_;
        _moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        currentSpeed_.x += speed.x / elapsed.asMicroseconds() * acceleration_;
        _moved = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        currentSpeed_.y -= speed.y / elapsed.asMicroseconds() * acceleration_;
        _moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += speed.y;
        currentSpeed_.y += speed.y / elapsed.asMicroseconds() * acceleration_;
        _rotation *= -1.;
        _moved = true;
    }

    if(_moved != user_input){
        user_input = _moved;
        if(user_input) sprite_.setTexture(textures_["engine_on"]);
        else sprite_.setTexture(textures_["engine_off"]);
    }

    currentSpeed_.x = std::clamp(currentSpeed_.x, -speed.x, speed.x);
    currentSpeed_.y = std::clamp(currentSpeed_.y, -speed.y, speed.y);

    movement = sf::Vector2f(currentSpeed_);
    _rotation = (currentSpeed_.x / speed.x) * _rotation_degrees;

    // apply the movement
    sprite_.move(movement);
    sprite_.setRotation(_rotation);
}

void Player::setRotationAcceleration(float rotationAcceleration) {
    acceleration_ = rotationAcceleration;
}

float Player::getRotationAcceleration() const {
    return acceleration_;
}

void Player::multiplyRotationAcceleration(float k) {
    acceleration_ *= k;
}

void Player::checkEnemyCollision(const std::vector<Enemy>& enemies){
    sf::FloatRect bounds = sprite_.getGlobalBounds();
    for (const auto& enemy : enemies) {
        sf::FloatRect enemyBounds = enemy.getSprite().getGlobalBounds();
        if (bounds.intersects(enemyBounds)) {
            // Player and enemy have collided
            alive_ = false;
            return;
        }
    }
}
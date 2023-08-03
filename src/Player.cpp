#include "Player.h"

Player::Player() = default;

void Player::init(const sf::Vector2u& windowSize, const sf::Texture& texture) {
    addTexture("engine_off", texture);
    sprite_.setTexture(textures_["engine_off"]);
    windowSize_ = windowSize;
    // set initial position at the bottom of the screen
    float x = windowSize.x / 2. - texture.getSize().x / 2.;
    float y = windowSize.y - texture.getSize().y;
    position_ = sf::Vector2f(x,y);

    sprite_.setPosition(position_);
    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
    alive_ = true;
    first_shot_fired_ = false;
    killed_by_bullet_ = false;
    engineForce_ = 80.0;
    angularVel_ = 0;
    maxAngularVel_ = 180;
    maxLinearVel_ = 50;
    angularAcc_ = 360;
    linearDecConst_ = 2.0;
}

void Player::update(const sf::Vector2f& speed, std::vector<Bullet>& bullets) {
    sf::Time elapsed = updateClock_.getElapsedTime();
    updateClock_.restart();

    userMovement(elapsed);
    // keep the player_ inside the screen bounds
    sf::Vector2f position = sprite_.getPosition();
    sf::Vector2u size = sprite_.getTexture()->getSize();
    sf::Vector2f half_size = sf::Vector2f(size.x/2., size.y/2.);

    if (position.x < half_size.x) { position.x = half_size.x, velocity_.x = 0.f; }
    if (position.y < half_size.y) { position.y = half_size.y, velocity_.y = 0.f; }
    if (position.x > windowSize_.x - half_size.x) { position.x = windowSize_.x - half_size.x, velocity_.x = 0.f; }
    if (position.y > windowSize_.y - half_size.y) { position.y = windowSize_.y - half_size.y, velocity_.y = 0.f; }

    sprite_.setPosition(position);
    checkBulletsCollision(bullets);
}

void Player::userMovement(const sf::Time& deltaTime){
    bool _moved = false;
    float _deltaTime = deltaTime.asSeconds();
        // TODO clamp vel, improve Down force
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        // Oblicz kierunek siły silnika
        sf::Vector2f _engineForceDirection(sinf(rotation_ * M_PI / 180.0f), -cosf(rotation_ * M_PI / 180.0f));
        // Oblicz przyspieszenie wynikające z siły silnika
        sf::Vector2f _acceleration = _engineForceDirection * engineForce_;
        // Dodaj przyspieszenie do prędkości
        velocity_ += _acceleration * _deltaTime;

        _moved = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        float _force = engineForce_ / 3;
        // Oblicz kierunek siły silnika
        sf::Vector2f _engineForceDirection(sinf(rotation_ * M_PI / 180.0f), -cosf(rotation_ * M_PI / 180.0f));
        // Oblicz przyspieszenie wynikające z siły silnika
        sf::Vector2f _acceleration = _engineForceDirection * _force;
        // Dodaj przyspieszenie do prędkości
        velocity_ -= _acceleration * _deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        angularVel_ -= angularAcc_ * _deltaTime;
        if (angularVel_ < -maxAngularVel_)  angularVel_ = -maxAngularVel_;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        angularVel_ += angularAcc_ * _deltaTime;
        if (angularVel_ > maxAngularVel_)   angularVel_ = maxAngularVel_;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {

        // Oblicz kierunek przeciwny do kierunku prędkości
        sf::Vector2f decelerationDirection = -normalize(velocity_);
        sf::Vector2f deceleration = decelerationDirection * engineForce_  * linearDecConst_;
        // Dodaj przyspieszenie hamujące do prędkości
        velocity_ += deceleration * _deltaTime;
    }

    // Zaktualizuj pozycję rakiety
    position_ += velocity_ * _deltaTime;
    // Zaktualizuj kąt rakiety
    rotation_ += angularVel_ * _deltaTime;

    sprite_.setPosition(position_);
    sprite_.setRotation(rotation_);

    if(_moved != user_input){
        user_input = _moved;
        if(user_input) sprite_.setTexture(textures_["engine_on"]);
        else sprite_.setTexture(textures_["engine_off"]);
    }

}

void Player::setEngineForce(float engineForce) { engineForce_ = engineForce; }

float Player::getEngineForce() const { return engineForce_; }

void Player::multiplyEngineForce(float k) { engineForce_ *= k; }

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
#include "Player.h"

Player::Player() = default;

void Player::init(const sf::Vector2u& windowSize, const sf::Texture& texture) {
    addTexture("engine_off", texture);
    sprite_.setTexture(textures_["engine_off"]);
    windowSize_ = windowSize;
    // set initial position at the bottom of the screen
    float x = windowSize.x / 2. - texture.getSize().x / 2.;
    float y = windowSize.y / 2. - texture.getSize().y / 2.;
    position_ = sf::Vector2f(x,y);

    sprite_.setPosition(position_);
    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
    alive_ = true;
    first_shot_fired_ = false;
    killed_by_bullet_ = false;
    linearAcc_ = 100.;
    angularVel_ = 0.;
    maxAngularVel_ = 180.;
    maxLinearVel_ = 50.;
    angularAcc_ = 300.;
    breakDecc_ = 200.;
    constDecc_ = 10.;
    engineDeccDivider_ = 2.;
    // TODO angular decceleration, black holes!/w gravity,
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

    float _x_acc = 0.f, _theta = 0.f;
    bool _brake = false;

    if (sf::Joystick::isConnected(0)) {
        _x_acc = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);  // Y lewego analoga
        _x_acc /= 100.; // (0 .. 1)

        _theta = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);  // X lewego analoga
        _theta /= 100.; // (0 .. 1)

        _brake = (sf::Joystick::isButtonPressed(0, 1));

        if (fabs(_x_acc) > 0.1) _moved = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        _x_acc = -1.0;
        _moved = true;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))   _x_acc = 1.0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _theta = -1.0;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _theta = 1.0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))   _brake = true; // dont touch when false

    calculateVelocity(_x_acc, _theta, _brake, _deltaTime);

    position_ += velocity_ * _deltaTime;
    rotation_ += angularVel_ * _deltaTime;

    sprite_.setPosition(position_);
    sprite_.setRotation(rotation_);

    if(_moved != user_input_){
        user_input_ = _moved;
        if(user_input_) sprite_.setTexture(textures_["engine_on"]);
        else sprite_.setTexture(textures_["engine_off"]);
    }
    user_input_ = _moved;
}

void Player::setlinearAcc(float linearAcc) { linearAcc_ = linearAcc; }

float Player::getlinearAcc() const { return linearAcc_; }

void Player::multiplyEngineForce(float k) { linearAcc_ *= k; }

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

void Player::calculateVelocity(const float& x_acc, const float& y_acc, const bool& brake, const float& deltaTime) {
    float _x_acc = x_acc;
    if (_x_acc < 0) _x_acc /= engineDeccDivider_;

    float _y_acc = y_acc;  // X lewego analoga

    angularVel_ += angularAcc_ * deltaTime * _y_acc;
    angularVel_ = std::clamp(angularVel_, -maxAngularVel_, maxAngularVel_);
    if (angularVel_ < -maxAngularVel_)  angularVel_ = -maxAngularVel_;

    // Oblicz kierunek siły silnika
    sf::Vector2f _engineForceDirection(sinf(-rotation_ * M_PI / 180.0f), cosf(rotation_ * M_PI / 180.0f));
    // Oblicz przyspieszenie wynikające z siły silnika
    sf::Vector2f _acceleration = _engineForceDirection * linearAcc_ * _x_acc;
    // Dodaj przyspieszenie do prędkości
    velocity_ += _acceleration * deltaTime;

    if (brake){
        // Oblicz kierunek przeciwny do kierunku prędkości
        sf::Vector2f decelerationDirection = -normalize(velocity_);
        sf::Vector2f deceleration = decelerationDirection * breakDecc_;
        // Dodaj przyspieszenie hamujące do prędkości
        velocity_ += deceleration * deltaTime;
    }
    // Oblicz kierunek przeciwny do kierunku prędkości
    sf::Vector2f decelerationDirection = -normalize(velocity_);
    sf::Vector2f deceleration = decelerationDirection * constDecc_;
    // Dodaj przyspieszenie hamujące do prędkości
    velocity_ += deceleration * deltaTime;
}

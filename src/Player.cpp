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
    decelerationDivider_ = 2.;

    linAcc_ = 100.;
    linBreakDecc_ = 200.;
    linConstDecc_ = 10.;
    maxLinearVel_ = 200.;
    angularVel_ = 0.;
    maxAngularVel_ = 180.;
    angAcc_ = 300.;
    angBreakDecc_ = 60.;
    angConstDecc_ = 10.;

    // TODO  black holes!/w gravity,
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
    bool _boost = false;

    if (sf::Joystick::isConnected(0)) {
        _x_acc = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);  // Y lewego analoga
        _x_acc /= 100.; // (0 .. 1)

        _theta = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);  // X lewego analoga
        _theta /= 100.; // (0 .. 1)

        _brake = (sf::Joystick::isButtonPressed(0, 1));
        _boost = (sf::Joystick::isButtonPressed(0, 2)); // TODO

        if (fabs(_x_acc) > 0.1) _moved = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        _x_acc = -1.0;
        _moved = true;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))   _x_acc = 1.f / decelerationDivider_;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _theta = -1.0;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _theta = 1.0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))   _boost = true; // dont touch when false
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) _brake = true; // dont touch when false

    boost_active_ = _boost;
    if (boost_active_) {_x_acc -= 1.5; _moved = true;}
    calculateVelocity(_x_acc, _theta, _brake, _deltaTime);

    if (length(velocity_) > maxLinearVel_)  velocity_ = normalize(velocity_) * maxLinearVel_;

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

void Player::setLinearAcc(float linearAcc) { linAcc_ = linearAcc; }

float Player::getlinearAcc() const { return linAcc_; }

void Player::multiplyLinearAcc(float k) { linAcc_ *= k; }

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

void Player::calculateVelocity(const float& lin_acc, const float& theta_acc, const bool& brake, const float& deltaTime) {
    float _lin_acc = lin_acc;
    if (_lin_acc < 0) _lin_acc /= decelerationDivider_;  // if backward worse acceleration

    float _theta = theta_acc;

    calculateAngularVelocity(_theta, deltaTime);

    sf::Vector2f _engineForceDirection = calculateForceDirection();
    sf::Vector2f _acceleration = calculateAcceleration(_engineForceDirection,
                                                       _lin_acc, deltaTime);
    velocity_ += _acceleration;

    sf::Vector2f deceleration = calculateDeceleration(deltaTime);
    velocity_ += deceleration;

    if (brake){
        deceleration = calculateBrakeDeceleration(deltaTime);
        velocity_ += deceleration;
        angularVel_ -= sgn(angularVel_) * angBreakDecc_ * deltaTime;
    }
}

void Player::calculateAngularVelocity(float theta_acc, float deltaTime) {
    float _sgnDeccVel = sgn(angularVel_) * (angConstDecc_ * deltaTime);
    angularVel_ += (angAcc_ * deltaTime * theta_acc) + _sgnDeccVel;
    angularVel_ = std::clamp(angularVel_, -maxAngularVel_, maxAngularVel_);
    if (angularVel_ < -maxAngularVel_)  angularVel_ = -maxAngularVel_;
}

sf::Vector2f Player::calculateForceDirection() {
    return sf::Vector2f(sinf(-rotation_ * M_PI / 180.0f), cosf(rotation_ * M_PI / 180.0f));
}

sf::Vector2f Player::calculateAcceleration(sf::Vector2f _engineForceDirection, float _x_acc, float deltaTime) {
    return _engineForceDirection * linAcc_ * _x_acc * deltaTime;
}

sf::Vector2f Player::calculateDeceleration(float deltaTime) {
    sf::Vector2f decelerationDirection = -normalize(velocity_);
    return decelerationDirection * linConstDecc_ * deltaTime;
}

sf::Vector2f Player::calculateBrakeDeceleration(float deltaTime) {
    sf::Vector2f decelerationDirection = -normalize(velocity_);
    return decelerationDirection * linBreakDecc_ * deltaTime;
}

template<typename T>
int Player::sgn(T val) { return (T(0) < val) - (val < T(0)); }

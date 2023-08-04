#include "Player.h"

Player::Player(const sf::Vector2u &windowSize, std::map<std::string, sf::Texture> &textures) : textures_(textures) {
    windowSize_ = windowSize;
    init();
}

void Player::init() {
    for (const auto& texturePair : textures_)   addSprite(texturePair.first, texturePair.second);
    mainSprite_ = sprites_["main"];

    // set initial position at the bottom of the screen
    float x = windowSize_.x / 2. - textures_["main"].getSize().x / 2.;
    float y = windowSize_.y / 2. - textures_["main"].getSize().y / 2.;
    position_ = sf::Vector2f(x,y);

    mainSprite_.setOrigin(mainSprite_.getLocalBounds().width / 2, mainSprite_.getLocalBounds().height / 2);
    mainSprite_.setPosition(position_);
    alive_ = true;
    firstShotFired_ = false;
    killedByBullet_ = false;
    decelerationDivider_ = 2.;

    linAcc_ = 100.;
    linBreakDecc_ = 20.;
    linConstDecc_ = 10.;
    maxLinearVel_ = 200.;
    maxAngularVel_ = 180.;
    angAcc_ = 300.;
    angBreakDecc_ = 30.;
    angConstDecc_ = 15.;

    // TODO  black holes!/w gravity,
}

void Player::update(std::vector<Bullet>& bullets, const std::vector<Enemy>& enemies) {
    sf::Time elapsed = updateClock_.getElapsedTime();
    updateClock_.restart();
    userMovement(elapsed);
    // keep the player_ inside the screen bounds
    sf::Vector2f position = mainSprite_.getPosition();
    sf::Vector2u size = mainSprite_.getTexture()->getSize();
    sf::Vector2f half_size = sf::Vector2f(size.x/2., size.y/2.);

    if (position.x < half_size.x) { position.x = half_size.x, velocity_.x = 0.f; }
    if (position.y < half_size.y) { position.y = half_size.y, velocity_.y = 0.f; }
    if (position.x > windowSize_.x - half_size.x) { position.x = windowSize_.x - half_size.x, velocity_.x = 0.f; }
    if (position.y > windowSize_.y - half_size.y) { position.y = windowSize_.y - half_size.y, velocity_.y = 0.f; }

    mainSprite_.setPosition(position);

    // Ustaw pozycje płomieni silnika
    sf::Vector2f flameDisplacement(0.f, 0.f); // wektor przesunięcia płomieni
    float rotationRadians = rotation_ * M_PI / 180.0f; // konwersja stopni na radiany

    // Oblicz nowy wektor przesunięcia na podstawie rotacji statku
    sf::Vector2f rotatedFlameDisplacement(
            flameDisplacement.x * cos(rotationRadians) - flameDisplacement.y * sin(rotationRadians),
            flameDisplacement.x * sin(rotationRadians) + flameDisplacement.y * cos(rotationRadians)
    );
    // Dodaj obliczony wektor przesunięcia do pozycji statku, aby uzyskać nową pozycję płomieni
    sf::Vector2f flamePosition = position_ + rotatedFlameDisplacement;
    sprites_["engine_on"].setPosition(flamePosition);
    sprites_["boost"].setPosition(flamePosition);

    // Ustaw rotację płomieni silnika na tę samą, co statek
    sprites_["engine_on"].setRotation(rotation_);
    sprites_["boost"].setRotation(rotation_);

    checkBulletsCollision(bullets);
    checkEnemyCollision(enemies);
}

void Player::userMovement(const sf::Time& deltaTime){
    float _deltaTime = deltaTime.asSeconds();

    sf::Vector2f _userVelocity = getInput();
    calculateVelocity(_userVelocity.x, _userVelocity.y, _deltaTime);

    if (length(velocity_) > maxLinearVel_)  velocity_ = normalize(velocity_) * maxLinearVel_;

    position_ += velocity_ * _deltaTime;
    rotation_ += angularVel_ * _deltaTime;

    mainSprite_.setPosition(position_);
    mainSprite_.setRotation(rotation_);


}
sf::Vector2f Player::getInput() {
    bool _moved = false;

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

    if (_boost) {_x_acc -= 1.5; _moved = true;}

    boostActive_ = _boost;
    brakeActive_ = _brake;
    userInput_ = _moved;

    return {_x_acc, _theta};
}

void Player::setLinearAcc(float linearAcc) { linAcc_ = linearAcc; }

float Player::getlinearAcc() const { return linAcc_; }

void Player::multiplyLinearAcc(float k) { linAcc_ *= k; }

void Player::checkEnemyCollision(const std::vector<Enemy>& enemies){
    sf::FloatRect bounds = mainSprite_.getGlobalBounds();
    for (const auto& enemy : enemies) {
        sf::FloatRect enemyBounds = enemy.getSprite().getGlobalBounds();
        if (bounds.intersects(enemyBounds)) {
            // Player and enemy have collided
            alive_ = false;
            return;
        }
    }
}

void Player::calculateVelocity(const float& lin_acc, const float& theta_acc, const float& deltaTime) {
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

    if (brakeActive_){
        deceleration = calculateBrakeDeceleration(deltaTime);
        velocity_ += deceleration;
        angularVel_ -= sgn(angularVel_) * angBreakDecc_ * deltaTime;
    }
}

void Player::calculateAngularVelocity(float theta_acc, float deltaTime) {
    float _sgnDeccVel = sgn(angularVel_) * (angConstDecc_ * deltaTime);
    angularVel_ += (angAcc_ * deltaTime * theta_acc) - _sgnDeccVel;
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

void Player::draw(sf::RenderWindow& window) const {
    window.draw(mainSprite_);
    if (boostActive_)  window.draw(sprites_.at("boost"));
    else if (userInput_)  window.draw(sprites_.at("engine_on"));
}


template<typename T>
int Player::sgn(T val) { return (T(0) < val) - (val < T(0)); }

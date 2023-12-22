#include "Player.h"

Player::Player(sf::Vector2f spawn_point, const std::map<std::string, sf::Texture> &textures){
    pos_ = spawn_point;

    radius_ = 30;
    maxLinAcc_ = 100.;
    maxAngAcc_ = 300.;
    linBreakDecc_ = 80.;
    linConstDecc_ = 10.;
    maxLinVel_ = 200.;
    maxAngVel_ = 180.;
    angBreakDecc_ = 30.;
    angConstDecc_ = 15.;

    maxHp_ = 5;
    hp_ = maxHp_;
    spriteInit(textures);
}

void Player::update(float deltaTime, const sf::Vector2f& netForce) {
    setNetForce(netForce);
    sf::Vector2f _userInput = getInput(); // Linear + Angular acc
    linAcc_ = _userInput.x * maxLinAcc_;
    angAcc_ = _userInput.y * maxAngAcc_;
    updateVel(deltaTime);
    if (vectorLength(linVel_) > maxLinVel_) linVel_ = vectorNormalize(linVel_) * maxLinVel_;
    updateSprites();
    if (hp_ == 0) alive_ = false;
}

sf::Vector2f Player::getInput() {
    bool _moved = false;

    float _x_acc = 0.f, _theta = 0.f;
    bool _brake = false;
    bool _boost = false;

    if (sf::Joystick::isConnected(0)) {
        _x_acc = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);  // Y lewego analoga
        _x_acc /= 100.; // (-1 .. 1)

        _theta = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);  // X lewego analoga
        _theta /= 100.; // (-1 .. 1)

        _brake = (sf::Joystick::isButtonPressed(0, 1));
        _boost = (sf::Joystick::isButtonPressed(0, 2)); // TODO check button

        if (fabs(_x_acc) > 0.1) _moved = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        _x_acc = 1.0;
        _moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _theta = -1.0;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _theta = 1.0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))   _boost = true; // dont touch when false
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) _brake = true; // dont touch when false

    if (_boost) {_x_acc += 1.5; _moved = true;}

    boostActive_ = _boost;
    brakeActive_ = _brake;
    userInput_ = _moved;

    return {_x_acc, _theta};
}


void Player::updateVel(float deltaTime) {
    // Linear
    calculateLinVel(deltaTime);
    sf::Vector2f _deltaNetForce = netForce_ * deltaTime; // force from space objects
    sf::Vector2f _deltaDecFroce= calculateDeceleration(linConstDecc_, deltaTime); // constant deceleration
    linVel_ += (_deltaNetForce + _deltaDecFroce);

    // Angular
    calculateAngVel(deltaTime);
    int angVelSign = getSign(int(angVel_));
    float _sgnDecelerationVel =  angVelSign * (angConstDecc_ * deltaTime);
    angVel_ -=_sgnDecelerationVel;

    if (brakeActive_){
        linVel_ += calculateDeceleration(linBreakDecc_, deltaTime);
        angVel_ -= angVelSign * angBreakDecc_ * deltaTime;
    }
}

sf::Vector2f Player::calculateDeceleration(float deceleration, float deltaTime) {
    sf::Vector2f decelerationDirection = -vectorNormalize(linVel_);
    return decelerationDirection * deceleration * deltaTime;
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(mainSprite_);
    if (boostActive_)  window.draw(sprites_.at("boost"));
    else if (userInput_)  window.draw(sprites_.at("engine_on"));
}

void Player::updateSprites() {
    mainSprite_.setPosition(pos_);
    mainSprite_.setRotation(rot_);

    // Ustaw pozycje płomieni silnika
    sf::Vector2f flameDisplacement(0.f, 0.f); // wektor przesunięcia płomieni
    float rotRadians = rot_ * M_PI / 180.0f; // konwersja stopni na radiany

    // Oblicz nowy wektor przesunięcia na podstawie rotacji statku
    sf::Vector2f rotatedFlameDisplacement(
            flameDisplacement.x * cos(rotRadians) - flameDisplacement.y * sin(rotRadians),
            flameDisplacement.x * sin(rotRadians) + flameDisplacement.y * cos(rotRadians)
    );
    // Dodaj obliczony wektor przesunięcia do pozycji statku, aby uzyskać nową pozycję płomieni
    sf::Vector2f flamePos = pos_ + rotatedFlameDisplacement;
    sprites_["engine_on"].setPosition(flamePos);
    sprites_["boost"].setPosition(flamePos);

    // Ustaw rotację płomieni silnika na tę samą, co statek
    sprites_["engine_on"].setRotation(rot_);
    sprites_["boost"].setRotation(rot_);
}

void Player::setNetForce(const sf::Vector2f& netForce) { netForce_ = netForce; }

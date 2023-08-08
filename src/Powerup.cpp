#include "Powerup.h"

Powerup::Powerup(const sf::Vector2f& position, const float& initRotation, const sf::Texture& texture) {
    initRotation_ = initRotation;
    rotation_ = initRotation_;
    position_ = position;
    maxLinVel_ = 80.;
    maxLinAcc_ = 50.;
    maxAngVel_ = 100;
    maxAngAcc_ = 200;
    linAcc_ = 50.;
    mass_ = 0.1;
    moveFrequency_ = 0.4;
    radius_ = 20;
    spriteInit(texture);
}

void Powerup::update(float deltaTime) {
    static float time = 0.0f;
    static float _rotation_add = 0.0f;
    mainSprite_.setPosition(position_);

    time += deltaTime;
    time = std::fmod(time, 2 * M_PI / moveFrequency_);

    _rotation_add =  90. * std::sin(2 * M_PI * moveFrequency_ * time);
    rotation_ =  initRotation_ + _rotation_add;
    calculateLinearVelocity(deltaTime);

}

void Powerup::draw(sf::RenderWindow &window) const {  window.draw(mainSprite_); }

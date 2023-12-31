#include "Powerup.h"

Powerup::Powerup(const sf::Vector2i spawn_point, const float& initRot, const sf::Texture& texture) {
    initRot_ = initRot;
    rot_ = initRot_;
    pos_ = sf::Vector2f(spawn_point);;
    maxLinVel_ = 80.;
    maxLinAcc_ = 50.;
    maxAngVel_ = 100;
    maxAngAcc_ = 200;
    linAcc_ = 50.;
    moveFrequency_ = 0.1;
    radius_ = 20;
    spriteInit(texture);

    buff_ = powerupType::acc1_2;
//    sf::IntRect bounds(15, 15, 30, 30);
//    setBounds(bounds);
    mainSprite_.setRotation(M_PI_2);
}

void Powerup::update(float deltaTime) {
    static float time = 0.0f;
    mainSprite_.setPosition(pos_);

    time += deltaTime;
    time = std::fmod(time, 2 * M_PI / moveFrequency_);

    float _rot_add =  90. * std::sin(2 * M_PI * moveFrequency_ * time);
    rot_ =  initRot_ + _rot_add;
    calculateLinVel(deltaTime);

}

void Powerup::draw(sf::RenderWindow &window) const {  window.draw(mainSprite_); }

Powerup::powerupType Powerup::getBuffType() const {
    return buff_;
}

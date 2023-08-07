#include "Powerup.h"

Powerup::Powerup(const sf::Vector2f& position, const float& initRotation, const sf::Texture& texture) {
    rotation_ = initRotation;
    position_ = position;
    maxLinVel_ = 100.;
    maxLinAcc_ = 50.;
    mass_ = 0.1;
    spriteInit(texture);
}

void Powerup::update(float linAcc, float deltaTime) {
    static float time = 0.0f;

    updateMainSpritePosition();
    time += deltaTime;
    // Zresetuj czas, gdy osiągnie pełny cykl sinusoidalny
    time = std::fmod(time, 2 * M_PI / moveFrequency_);

    linAcc_ = maxLinAcc_ * std::sin(2 * M_PI * moveFrequency_ * time);

    calculateLinearVelocity(deltaTime);
}

#include "Powerup.h"

Powerup::Powerup(const sf::Vector2f& position, const float& initRotation, const sf::Texture& texture) {
    rotation_ = initRotation;
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

    updateMainSpritePosition();
    time += deltaTime;
    // Zresetuj czas, gdy osiągnie pełny cykl sinusoidalny
    time = std::fmod(time, M_PI / moveFrequency_);

    angAcc_ = maxAngAcc_ * std::sin(2 * M_PI * moveFrequency_ * time);

    calculateLinearVelocity(deltaTime);

//    static float time = 0.0f; // Statyczna zmienna przechowująca całkowity upływający czas
//    time += deltaTime; // Aktualizacja czasu o wartość deltaTime
//
//    float frequency = 1.0f; // Częstotliwość ruchu sinusoidalnego
//    float amplitude = 50.0f; // Amplituda ruchu sinusoidalnego
//
//    // Oblicz wartość sinusoidalną
//    float sinusoidalValue = amplitude * std::sin(2 * M_PI * frequency * time);
//
//    // Oblicz kierunek liniowego przyspieszenia
//    sf::Vector2f linAccDirection = calculateLinAccDirection();
//
//    // Dodaj wartość sinusoidalną do kierunku przyspieszenia
//    linAccDirection.x += sinusoidalValue * std::cos(rotation_ * M_PI / 180.0f);
//    linAccDirection.y += sinusoidalValue * std::sin(rotation_ * M_PI / 180.0f);
//
//    // Oblicz nową prędkość liniową
//    sf::Vector2f deltaLinAccForce = calculateAcceleration(linAccDirection, deltaTime);
//    linVel_ += deltaLinAccForce;
//    if (vectorLength(linVel_) > maxLinVel_) linVel_ = vectorNormalize(linVel_) * maxLinVel_;
//
//    // Aktualizuj pozycję obiektu
//    position_ += linVel_ * deltaTime;
//
//    // Aktualizuj pozycję i inne właściwości obiektu
//    calculateAngularVelocity(deltaTime);
//    updateMainSpritePosition();


}

void Powerup::draw(sf::RenderWindow &window) const {  window.draw(mainSprite_); }

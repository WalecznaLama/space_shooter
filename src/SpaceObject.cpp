#include "SpaceObject.h"

const float SpaceObject::G_ = 100.f;

SpaceObject::SpaceObject (const sf::Texture &texture, const sf::Vector2f& initPosition,
                          const sf::Vector2f& initVelocity, const float initRotation,
                          const float radius, const float density)
        :  density_(density) {
    position_ = initPosition;
    linVel_ = initVelocity;
    rotation_ = initRotation;
    radius_ = radius;

    calculateMass(radius);
    spriteInit(texture);
}

float SpaceObject::calculateMass(float radius)  {
    float volume = (4. / 3.) * M_PI * std::pow(radius, 3);
    mass_ = volume * density_;
}

void SpaceObject::update() { updateMainSpritePosition(); }

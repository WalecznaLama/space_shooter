#include "SpaceObject.h"

const float SpaceObject::G_ = 100.f;

SpaceObject::SpaceObject (const sf::Texture &texture, const sf::Vector2f& initPos,
                          const sf::Vector2f& initVel, const float initRot,
                          const int radius, const float density)
        :  density_(density) {
    pos_ = initPos;
    linVel_ = initVel;
    rot_ = initRot;
    radius_ = radius;

    mass_ = calculateMass(radius);
    spriteInit(texture);
}

float SpaceObject::calculateMass(int radius)  {
    float volume = (4. / 3.) * M_PI * std::pow(radius, 3);
    return volume * density_;
}

void SpaceObject::update() {
    mainSprite_.setPosition(pos_);
    mainSprite_.setRotation(rot_);
}

float SpaceObject::getMass() const {
    return mass_;
}

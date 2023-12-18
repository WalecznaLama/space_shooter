#ifndef SPACE_SHOOTER_SPACEOBJECT_H
#define SPACE_SHOOTER_SPACEOBJECT_H

#include "Object.h"

class SpaceObject : public Object{
public:
    static const float G_;
    SpaceObject(const sf::Texture &texture, const sf::Vector2f& initPos,
                const sf::Vector2f& initVel, float initRot,
                float radius, float density);

    void update();
    float getMass() const;

private:
    float density_;
    float mass_;
    float calculateMass(float radius);
};

#endif //SPACE_SHOOTER_SPACEOBJECT_H

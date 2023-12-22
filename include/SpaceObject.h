#ifndef SPACE_SHOOTER_SPACEOBJECT_H
#define SPACE_SHOOTER_SPACEOBJECT_H

#include "Object.h"

class SpaceObject : public Object{
public:
    static const float G_;
    SpaceObject(const sf::Texture &texture, const sf::Vector2f& initPos,
                const sf::Vector2f& initVel, float initRot,
                int radius, float density);

    void update();
    float getMass() const;
    void draw(sf::RenderWindow& window) const;

private:
    float density_;
    float mass_;
    float calculateMass(int radius);
};

#endif //SPACE_SHOOTER_SPACEOBJECT_H

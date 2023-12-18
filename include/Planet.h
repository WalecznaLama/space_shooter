#ifndef SPACE_SHOOTER_PLANET_H
#define SPACE_SHOOTER_PLANET_H

#include "SpaceObject.h"

class Planet : public SpaceObject {
public:
    static const float DEFAULT_DENSITY;
    Planet(const sf::Texture &texture, const sf::Vector2f& pos, const sf::Vector2f& vel,
           float rot, float radius);
};

#endif //SPACE_SHOOTER_PLANET_H

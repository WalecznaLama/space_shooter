#include "SpaceObject/Planet.h"

const float Planet::DEFAULT_DENSITY = 0.0005f;
//const float Planet::DEFAULT_DENSITY = 0.002f;

Planet::Planet(const sf::Texture &texture, const sf::Vector2f &position, const sf::Vector2f &vel,
               const float rot, const int radius) :
        SpaceObject(texture, position, vel,
                    rot, radius, DEFAULT_DENSITY) {

    const float factor = (2. * radius) / getSprite().getGlobalBounds().height;
    scaleSprite(mainSprite_,factor, factor);
}
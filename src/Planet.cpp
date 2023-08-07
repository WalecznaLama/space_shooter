#include "Planet.h"

const float Planet::DEFAULT_DENSITY = 0.0005f;

Planet::Planet(const sf::Texture &texture, const sf::Vector2f &position, const sf::Vector2f &velocity,
               const float rotation, const float radius) :
        SpaceObject(texture, position, velocity,
                    rotation, radius, DEFAULT_DENSITY) {

    const float factor = (2. * radius) / getSprite().getGlobalBounds().height;
    scaleSprite(mainSprite_,factor, factor);
}
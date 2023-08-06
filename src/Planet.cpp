#include "Planet.h"

const float Planet::DEFAULT_DENSITY = 1.0f;

Planet::Planet(const sf::Texture &texture, const sf::Vector2f &position, const sf::Vector2f &velocity,
               const float rotation, const float radius) :
        SpaceObject(texture, position, velocity,
                    rotation, radius, DEFAULT_DENSITY) {
    scaleSprite(0.2, 0.2);
}
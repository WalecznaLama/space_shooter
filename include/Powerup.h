#ifndef SPACE_SHOOTER_POWERUP_H
#define SPACE_SHOOTER_POWERUP_H

#include "Object.h"

class Powerup : public Object {
public:
    Powerup(const sf::Vector2f& position, const float& initRotation, const sf::Texture& texture);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;

private:
    float moveFrequency_;
    float initRotation_;
};


#endif //SPACE_SHOOTER_POWERUP_H

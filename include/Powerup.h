#ifndef SPACE_SHOOTER_POWERUP_H
#define SPACE_SHOOTER_POWERUP_H

#include "Object.h"

class Powerup : public Object {
public:
    Powerup(sf::Vector2i spawn_point, const float& initRot, const sf::Texture& texture);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;

private:
    float moveFrequency_;
    float initRot_;
};


#endif //SPACE_SHOOTER_POWERUP_H

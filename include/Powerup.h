#ifndef SPACE_SHOOTER_POWERUP_H
#define SPACE_SHOOTER_POWERUP_H

#include "PassiveObject.h"

class Powerup : public PassiveObject {
public:
    Powerup(const sf::Vector2u& windowSize, const sf::Texture& texture);
    void update(float dx, float dy, float d_range);

private:
    float d_from_spawn;
    bool going_right;
};


#endif //SPACE_SHOOTER_POWERUP_H

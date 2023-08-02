#ifndef SPACE_SHOOTER_POWERUP_H
#define SPACE_SHOOTER_POWERUP_H

#include "PassiveObject.h"

class Powerup : public PassiveObject {
public:
    Powerup(const sf::Vector2u& windowSize, const sf::Texture& texture);
    void update(const float& speed) override;

private:
    float d_range;
    float d_from_spawn;
    bool going_right;
};


#endif //SPACE_SHOOTER_POWERUP_H

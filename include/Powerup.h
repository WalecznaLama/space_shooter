#ifndef SPACE_SHOOTER_POWERUP_H
#define SPACE_SHOOTER_POWERUP_H

#include "PassiveObject.h"

class Powerup : public PassiveObject {
public:
    Powerup(const sf::Vector2u& windowSize, const sf::Texture& texture);
    void update(const float& speed) override;

private:
    float d_range_;
    float d_from_spawn_;
    bool going_right_;
};


#endif //SPACE_SHOOTER_POWERUP_H

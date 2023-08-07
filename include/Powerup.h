#ifndef SPACE_SHOOTER_POWERUP_H
#define SPACE_SHOOTER_POWERUP_H

#include "PassiveObject.h"

class Powerup : public PassiveObject {
public:
    Powerup(const sf::Vector2f& position, const float& initRotation, const sf::Texture& texture);
    void update(float deltaTime) override;

private:
    float moveFrequency_;
};


#endif //SPACE_SHOOTER_POWERUP_H

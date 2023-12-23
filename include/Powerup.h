#ifndef SPACE_SHOOTER_POWERUP_H
#define SPACE_SHOOTER_POWERUP_H

#include "Object.h"

class Powerup : public Object {
public:
    Powerup(sf::Vector2i spawn_point, const float& initRot, const sf::Texture& texture);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    enum powerupType {acc1_2, vel1_5};
    powerupType getBuffType() const;

private:
    float moveFrequency_;
    float initRot_;
    powerupType buff_;
};


#endif //SPACE_SHOOTER_POWERUP_H

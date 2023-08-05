#ifndef SPACE_SHOOTER_BULLET_H
#define SPACE_SHOOTER_BULLET_H

#include "PassiveObject.h"
#include <cmath>

class Bullet : public PassiveObject {

public:
    Bullet(const sf::Vector2f& position, const sf::Texture& texture, const float& angle);
    void update(const float &velocity) override;

private:
    float initAngle_;
};

#endif //SPACE_SHOOTER_BULLET_H

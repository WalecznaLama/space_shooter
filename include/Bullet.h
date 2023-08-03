#ifndef SPACE_SHOOTER_BULLET_H
#define SPACE_SHOOTER_BULLET_H

#include "PassiveObject.h"
#include <cmath>

class Bullet : public PassiveObject {

public:
    Bullet(const sf::Vector2f& position, const sf::Texture& texture, const float& angle);
    void update(const float &speed) override;

private:
    float init_angle_;
};

#endif //SPACE_SHOOTER_BULLET_H

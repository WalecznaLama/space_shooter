#ifndef SPACE_SHOOTER_BULLETENEMY_H
#define SPACE_SHOOTER_BULLETENEMY_H

#include "Projectile.h"

class BulletEnemy : public Projectile {

public:
    BulletEnemy(const sf::Texture &texture, const sf::Vector2f& initPos, const sf::Vector2f& initVel, const float& initRot);
    void update(float deltaTime) override;
};

#endif //SPACE_SHOOTER_BULLETENEMY_H

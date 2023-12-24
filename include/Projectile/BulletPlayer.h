#ifndef SPACE_SHOOTER_BULLETPLAYER_H
#define SPACE_SHOOTER_BULLETPLAYER_H

#include "Projectile.h"

class BulletPlayer : public Projectile {

public:
    BulletPlayer(const sf::Texture &texture, const sf::Vector2f& initPos, const sf::Vector2f& initVel, const float& initRot);
    void update(float deltaTime) override;
};

#endif //SPACE_SHOOTER_BULLETPLAYER_H

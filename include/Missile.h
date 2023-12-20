#ifndef SPACE_SHOOTER_MISSILE_H
#define SPACE_SHOOTER_MISSILE_H

#include "Projectile.h"


class Missile : public Projectile {
public:
    static const int DEFAULT_RADIUS;
    static const float DEFAULT_MAX_LIN_VEL;
    static const float DEFAULT_LIN_ACC;
    static const int DEFAULT_DAMAGE;

    Missile(const sf::Texture &texture, const sf::Vector2f& initPos, const sf::Vector2f& spawnOffset,
            const sf::Vector2f& initVel, float initRot);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
};


#endif //SPACE_SHOOTER_MISSILE_H

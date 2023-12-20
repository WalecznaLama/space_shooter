#include "Missile.h"

const int Missile::DEFAULT_RADIUS = 10.;
const float Missile::DEFAULT_MAX_LIN_VEL = 600.;
const float Missile::DEFAULT_LIN_ACC = 200.;
const int Missile::DEFAULT_DAMAGE = 2;

Missile::Missile(const sf::Texture &texture, const sf::Vector2f &initPos, const sf::Vector2f &spawnOffset,
                 const sf::Vector2f &initVel, float initRot) :
        Projectile(texture, initPos, spawnOffset, initVel, initRot, DEFAULT_RADIUS,
                   DEFAULT_MAX_LIN_VEL, DEFAULT_LIN_ACC, DEFAULT_DAMAGE)
        {  }

void Missile::update(float deltaTime) {
    mainSprite_.setPosition(pos_);
    mainSprite_.setRotation(rot_);
    calculateLinVel(deltaTime);
}

void Missile::draw(sf::RenderWindow &window) const {
    Projectile::draw(window);
}

#ifndef SPACE_SHOOTER_PROJECTILE_H
#define SPACE_SHOOTER_PROJECTILE_H

#include "Object.h"

class Projectile : public Object {
public:
    enum projectileType {bullet, missile};
    Projectile(const sf::Texture &texture, const sf::Vector2f &initPos, const sf::Vector2f &initVel, float initRot);
    virtual void draw(sf::RenderWindow& window) const;
    int getDamage() const;
    virtual void update(float deltaTime) = 0;

protected:
    int damage_;
    sf::Vector2f spawnOffset_;
};


#endif //SPACE_SHOOTER_PROJECTILE_H

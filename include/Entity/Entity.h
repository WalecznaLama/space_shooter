#ifndef SPACE_SHOOTER_ENTITY_H
#define SPACE_SHOOTER_ENTITY_H

#include "Projectile/BulletPlayer.h"
#include <map>
#include <random>
#include "Object.h"

class Entity : public Object{

public:
    virtual void draw(sf::RenderWindow& window) const;
    bool canShoot(float time_to_shoot);
    void setDamage(int damage);

    void setHp(int hp);
    int getHp() const;

    void setMaxHp(int hp);
    int getMaxHp() const;

protected:
    sf::Clock shootClock_;
//    sf::Clock updateClock_;
    bool firstShotFired_;
    int hp_;
    int maxHp_;

};

#endif //SPACE_SHOOTER_ENTITY_H

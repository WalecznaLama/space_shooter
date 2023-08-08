#ifndef SPACE_SHOOTER_PROJECTILE_H
#define SPACE_SHOOTER_PROJECTILE_H

#include "Object.h"

class Projectile : public Object {
public:
    Projectile(const sf::Texture &texture, const sf::Vector2f& initPosition, const sf::Vector2f& spawnOffset,
               const sf::Vector2f& initVel, float initRotation, float radius, float maxLinVel, float linAcc,
               int damage, float angVel=0.,float angAcc=0., float maxAngVel=0., float maxAngAcc=0.);
    Projectile(const std::map<std::string, sf::Texture> &textures, const sf::Vector2f& initPosition,
               const sf::Vector2f& spawnOffset,const sf::Vector2f& initVel, float initRotation, float radius,
               float maxLinVel, float linAcc,int damage,
               float angVel=0.,float angAcc=0., float maxAngVel=0., float maxAngAcc=0.);
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) const;
    int getDamage() const;

private:
    void init(const sf::Vector2f& initPosition, const sf::Vector2f& spawnOffset,
              const sf::Vector2f& initVel, float initRotation, float radius, float maxLinVel, float linAcc,
              int damage, float angVel,float angAcc, float maxAngVel, float maxAngAcc);
    int damage_;
};


#endif //SPACE_SHOOTER_PROJECTILE_H

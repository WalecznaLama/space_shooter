#include "Projectile/Projectile.h"

Projectile::Projectile(const sf::Texture &texture, const sf::Vector2f &initPos,
                       const sf::Vector2f &initVel, float initRot){
    pos_ = initPos;
    rot_ = initRot;
    linVel_ = initVel;
    spriteInit(texture);
}


void Projectile::draw(sf::RenderWindow &window) const { window.draw(mainSprite_); }

int Projectile::getDamage() const { return damage_; }

#include "Projectile.h"

Projectile::Projectile(const sf::Texture &texture, const sf::Vector2f& initPos, const sf::Vector2f& spawnOffset,
                       const sf::Vector2f& initVel, float initRot, int radius, float maxLinVel, float linAcc,
                       int damage,float angVel, float angAcc, float maxAngVel, float maxAngAcc) {
    init(initPos, spawnOffset, initVel, initRot, radius, maxLinVel,
         linAcc, damage, angVel, angAcc, maxAngVel, maxAngAcc);
    spriteInit(texture);
}

Projectile::Projectile(const std::map<std::string, sf::Texture> &textures, const sf::Vector2f &initPos,
                       const sf::Vector2f &spawnOffset, const sf::Vector2f &initVel, float initRot, int radius,
                       float maxLinVel, float linAcc, int damage, float angVel, float angAcc, float maxAngVel,
                       float maxAngAcc) {
    init(initPos, spawnOffset, initVel, initRot, radius, maxLinVel,
         linAcc, damage, angVel, angAcc, maxAngVel, maxAngAcc);
    spriteInit(textures);
}

void Projectile::draw(sf::RenderWindow &window) const { window.draw(mainSprite_); }

int Projectile::getDamage() const { return damage_; }

void Projectile::init(const sf::Vector2f& initPos, const sf::Vector2f& spawnOffset,
                      const sf::Vector2f& initVel, float initRot, int radius, float maxLinVel, float linAcc,
                      int damage, float angVel,float angAcc, float maxAngVel, float maxAngAcc) {
    pos_ = initPos;
    rot_ = initRot;
    float _rotRad = rot_ * (M_PI / 180.);

    float offsetX = spawnOffset.x * cosf(_rotRad) - spawnOffset.y * sinf(_rotRad);
    float offsetY = spawnOffset.x * sinf(_rotRad) + spawnOffset.y * cosf(_rotRad);

    pos_.x += offsetX;
    pos_.y += offsetY;

    damage_ = damage;

    linVel_ = initVel;
    maxLinVel_ = maxLinVel;
    linAcc_ = linAcc;
    radius_ = radius;

    angVel_ = angVel;
    angAcc_ = angAcc;
    maxAngVel_ = maxAngVel;
    maxAngAcc_ = maxAngAcc;
}

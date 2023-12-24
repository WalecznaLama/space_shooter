#include "Projectile/BulletPlayer.h"

BulletPlayer::BulletPlayer(const sf::Texture &texture, const sf::Vector2f& initPos,
                           const sf::Vector2f& initVel, const float& initRot) :
        Projectile(texture, initPos, initVel, initRot) {

    damage_ = 1;
    spawnOffset_ = {0, -30};

    maxLinVel_ = 1200.f;
    linAcc_ = 600.f;

    float _rotRad = rot_ * (M_PI / 180.);
    pos_.x += spawnOffset_.x * cosf(_rotRad) - spawnOffset_.y * sinf(_rotRad);
    pos_.y += spawnOffset_.x * sinf(_rotRad) + spawnOffset_.y * cosf(_rotRad);
}

void BulletPlayer::update(float deltaTime) {
    mainSprite_.setPosition(pos_);
    mainSprite_.setRotation(rot_);
    calculateLinVel(deltaTime);
}


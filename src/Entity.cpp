#include "Entity.h"

bool Entity::canShoot(float time_to_shoot){
    sf::Time elapsed = shootClock_.getElapsedTime();
    float interval;

    if (!firstShotFired_)  interval = time_to_shoot / 10.f; // TODO const
    else    interval = time_to_shoot;

    if (elapsed.asSeconds() >= interval) {
        shootClock_.restart();
        firstShotFired_ = true;
        return true;
    }
    return false;
}

void Entity::draw(sf::RenderWindow& window) const{ window.draw(mainSprite_); }

void Entity::setHp(int hp) { hp_ = hp; }
int Entity::getHp() const { return hp_; }

void Entity::setMaxHp(int hp) { maxHp_ = hp; }
int Entity::getMaxHp() const { return maxHp_; }

void Entity::setDamage(int damage) {
    hp_ = std::max(0, hp_ - damage);
    if (hp_ == 0) setIsAlive(false);
}

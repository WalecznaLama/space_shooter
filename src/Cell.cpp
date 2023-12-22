#include "Cell.h"

bool Cell::hasPlayer() const { return player_ != nullptr; }
Player *Cell::getPlayer() const  { return player_; }
void Cell::setPlayer(Player *player) { player_ = player; }

bool Cell::hasEnemy() const { return enemy_ != nullptr; }
Enemy *Cell::getEnemy() const  { return enemy_; }
void Cell::setEnemy(Enemy *enemy) { enemy_ = enemy; }

// Player Bullet
bool Cell::hasPlayerBullet() const { return playerBullet_ != nullptr; }
Bullet *Cell::getPlayerBullet() const  { return playerBullet_; }
void Cell::setPlayerBullet(Bullet *bullet) { playerBullet_ = bullet; }

// Enemy Bullets
bool Cell::hasEnemyBullet() const { return enemyBullet_ != nullptr; }
Bullet *Cell::getEnemyBullet() const  { return enemyBullet_; }
void Cell::setEnemyBullet(Bullet *bullet) { enemyBullet_ = bullet; }

bool Cell::hasSpaceObject() const { return spaceObject_ != nullptr; }
SpaceObject *Cell::getSpaceObject() const  { return spaceObject_; }
void Cell::setSpaceObject(SpaceObject *spaceObject) { spaceObject_ = spaceObject; }

bool Cell::hasPowerup() const { return powerup_ != nullptr; }
Powerup *Cell::getPowerup() const { return powerup_; }
void Cell::setPowerup(Powerup *powerup) { powerup_ = powerup; }

void Cell::clear_cell(){
    player_ = nullptr;
    enemy_ = nullptr;
    playerBullet_ = nullptr;
    enemyBullet_ = nullptr;
    powerup_ = nullptr;
    spaceObject_ = nullptr;
}

bool Cell::isOccupied() const {
    return hasPlayer() || hasEnemy() || hasPlayerBullet() || hasEnemyBullet() || hasSpaceObject();
}

bool Cell::isOccupiedEnemy() const { return hasEnemy() || hasEnemyBullet(); }

bool Cell::isPlayerProjectileCollide() const {
    return hasEnemy() || hasEnemyBullet() || hasSpaceObject();
}



#ifndef SPACE_SHOOTER_CELL_H
#define SPACE_SHOOTER_CELL_H

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Planet.h"
#include "Powerup.h"

class Cell {
public:
    Cell()
            : player_(nullptr), enemy_(nullptr), playerBullet_(nullptr), enemyBullet_(nullptr) {}
    // Player
    bool hasPlayer() const;
    Player* getPlayer() const;
    void setPlayer(Player* player);

    // Enemies
    bool hasEnemy() const;
    Enemy* getEnemy() const;
    void setEnemy(Enemy* enemy);

    // Player Bullets
    bool hasPlayerBullet() const;
    Bullet* getPlayerBullet() const;
    void setPlayerBullet(Bullet* bullet);

    // Enemy Bullets
    bool hasEnemyBullet() const;
    Bullet* getEnemyBullet() const;
    void setEnemyBullet(Bullet* bullet);

    // SpaceObject
    bool hasSpaceObject() const;
    SpaceObject* getSpaceObject() const;
    void setSpaceObject(SpaceObject* spaceObject);

    // Powerup
    bool hasPowerup() const;
    Powerup* getPowerup() const;
    void setPowerup(Powerup* powerup);

    void clear_cell();

    bool isOccupied() const;
    bool isOccupiedEnemy() const;
    bool isPlayerProjectileCollide() const;

private:
    Player* player_;
    Enemy* enemy_;
    Bullet* playerBullet_;
    Bullet* enemyBullet_;
    Powerup* powerup_;
    SpaceObject* spaceObject_;
};

#endif //SPACE_SHOOTER_CELL_H

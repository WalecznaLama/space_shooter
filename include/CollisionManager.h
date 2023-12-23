#ifndef SPACE_SHOOTER_COLLISIONMANAGER_H
#define SPACE_SHOOTER_COLLISIONMANAGER_H

#include "PlayerManager.h"
#include "EnemyManager.h"
#include "ProjectileManager.h"
#include "SpaceObjectManager.h"
#include "PowerupManager.h"

class CollisionManager {
public:
    CollisionManager(PlayerManager& playerManager, EnemyManager& enemyManager, ProjectileManager& projectileManager,
                     SpaceObjectManager& spaceObjectManager, PowerupManager& powerupManager);
    void update();

private:
    PlayerManager& playerManager_;
    EnemyManager& enemyManager_;
    ProjectileManager& projectileManager_;
    SpaceObjectManager& spaceObjectManager_;
    PowerupManager& powerupManager_;
};

#endif //SPACE_SHOOTER_COLLISIONMANAGER_H

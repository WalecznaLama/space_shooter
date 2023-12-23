#include "CollisionManager.h"

CollisionManager::CollisionManager(PlayerManager &playerManager, EnemyManager &enemyManager,
                                   ProjectileManager &projectileManager, SpaceObjectManager &spaceObjectManager,
                                   PowerupManager &powerupManager) :
                                   playerManager_(playerManager), enemyManager_(enemyManager),
                                   projectileManager_(projectileManager), spaceObjectManager_(spaceObjectManager),
                                   powerupManager_(powerupManager) { }

void CollisionManager::update() {
    auto _playerBounds = playerManager_.player_->getBounds();

    auto _enemyBullets = projectileManager_.enemyBullets_;
    for (auto & bullet : _enemyBullets) {
        auto _bounds = bullet->getBounds();
        if (_bounds.intersects(_playerBounds)) {
            playerManager_.player_->setDamage(2);
            bullet->setIsAlive(false);
        }
    }
    auto _playerBullets = projectileManager_.playerBullets_;
    auto _enemies = enemyManager_.enemies_;
    for (auto & bullet : _playerBullets) {
        auto _bounds = bullet->getBounds();
        for (auto & enemy : _enemies) {
            if (_bounds.intersects(enemy->getBounds())) {
                enemy->setDamage(2);
                bullet->setIsAlive(false);
            }
        }
    }
}

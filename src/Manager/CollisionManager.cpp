#include "Manager/CollisionManager.h"

CollisionManager::CollisionManager(PlayerManager &playerManager, EnemyManager &enemyManager,
                                   ProjectileManager &projectileManager, SpaceObjectManager &spaceObjectManager,
                                   PowerupManager &powerupManager) :
                                   playerManager_(playerManager), enemyManager_(enemyManager),
                                   projectileManager_(projectileManager), spaceObjectManager_(spaceObjectManager),
                                   powerupManager_(powerupManager) { }

void CollisionManager::update() {
    auto _playerBounds = playerManager_.player_->getSprite().getGlobalBounds();

    auto _enemyBullets = projectileManager_.enemyBullets_;
    for (auto & bullet : _enemyBullets) {
        auto _bounds = bullet->getSprite().getGlobalBounds();
        if (_bounds.intersects(_playerBounds)) {
            playerManager_.player_->setDamage(1);
            bullet->setIsAlive(false);
        }
    }
    auto _playerBullets = projectileManager_.playerBullets_;
    auto _enemies = enemyManager_.enemies_;
    for (auto & bullet : _playerBullets) {
        auto _bounds = bullet->getSprite().getGlobalBounds();
        for (auto & enemy : _enemies) {
            if (_bounds.intersects(enemy->getSprite().getGlobalBounds())) {
                enemy->setDamage(1);
                bullet->setIsAlive(false);
            }
        }
    }

    auto _powerups = powerupManager_.powerups_;
    for (auto & powerup : _powerups) {
        auto _bounds = powerup->getSprite().getGlobalBounds();
        if (_bounds.intersects(_playerBounds)) {
            powerup->setIsAlive(false);

            auto _buff = powerup->getBuffType();
            switch (_buff) {
                case Powerup::acc1_2:
                    playerManager_.player_->setMaxLinAcc(1.2 * playerManager_.player_->getMaxLinAcc());
                    break;

                case Powerup::vel1_5:
                    playerManager_.player_->setMaxLinVel(1.5 * playerManager_.player_->getMaxLinVel());
                    break;

                default:
                    break;
            }
        }
    }

    auto _spaceObjects = spaceObjectManager_.spaceObjects_;
    for (auto & spaceObject : _spaceObjects) {
        auto _bounds = spaceObject->getSprite().getGlobalBounds();
        if (_bounds.intersects(_playerBounds)) {

            playerManager_.player_->setLinVel({0.f, 0.f});
        }
    }
}

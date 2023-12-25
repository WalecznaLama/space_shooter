#include "Manager/CollisionManager.h"

CollisionManager::CollisionManager(PlayerManager &playerManager, EnemyManager &enemyManager,
                                   ProjectileManager &projectileManager, SpaceObjectManager &spaceObjectManager,
                                   PowerupManager &powerupManager) :
                                   playerManager_(playerManager), enemyManager_(enemyManager),
                                   projectileManager_(projectileManager), spaceObjectManager_(spaceObjectManager),
                                   powerupManager_(powerupManager) { }

void CollisionManager::update() {
    sf::Rect<float> _playerBounds = playerManager_.player_->getSprite().getGlobalBounds();

    // Obliczanie środka sprite'a
//    sf::Rect<float> bounds = {40, 60, 52, 52};
//    bounds.

//    // Tworzenie prostokąta ograniczającego
//    sf::RectangleShape _playerBounds;
//    _playerBounds.setSize(sf::Vector2f(bounds.width, bounds.height)); // Połowa rozmiaru sprite'a
//    _playerBounds.setPosition(playerManager_.player_->getPos()); // Wyśrodkowanie
////    boundsRect.setFillColor(sf::Color::Transparent);
////    boundsRect.setOutlineColor(sf::Color::Black);
//    _playerBounds.setOrigin(playerManager_.player_->getSprite().getOrigin());
////    boundsRect.setOutlineThickness(1.f);
//    _playerBounds.setRotation(playerManager_.player_->getRot()); // Ustawienie takiej samej rotacji jak sprite

    auto &_enemyBullets = projectileManager_.enemyBullets_;
    for (auto & bullet : _enemyBullets) {
        auto _bounds = bullet->getSprite().getGlobalBounds();
        if (_bounds.intersects(_playerBounds)) {
            playerManager_.player_->setDamage(1);
            bullet->setIsAlive(false);
        }
    }
    auto &_playerBullets = projectileManager_.playerBullets_;
    auto &_enemies = enemyManager_.enemies_;
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

    auto &_spaceObjects = spaceObjectManager_.spaceObjects_;
    for (auto& spaceObject : _spaceObjects) {
        sf::Vector2f centerSpaceObject =spaceObject->getPos();
        sf::Vector2f centerPlayer = playerManager_.player_->getPos();

        float distance = sqrt(pow(centerSpaceObject.x - centerPlayer.x, 2) +
                              pow(centerSpaceObject.y - centerPlayer.y, 2));

        if (distance < spaceObject->getRadius() + playerManager_.player_->getRadius()) {
            playerManager_.player_->setLinVel({0.f, 0.f});
            // Wykryto kolizję
        }
    }
}

#include "Manager/ProjectileManager.h"

ProjectileManager::ProjectileManager(const AssetManager& assetManager, Grid& grid) :
                                     grid_(grid),
                                     assetManager_(assetManager) {
}

void ProjectileManager::update(float deltaTime) {
    for (auto it = playerBullets_.begin(); it != playerBullets_.end(); /* pusta sekcja inkrementacji */) {
        auto &bullet = *it;
        bullet->update(deltaTime);
        sf::Vector2f displacement = bullet->getLinVel() * deltaTime; // calculate how far should move
        sf::Vector2f newPos = bullet->getPos() + displacement; // calculate new position
        auto oldCell = grid_.getCell(bullet->getPos());
        oldCell.clear_cell();
        if (grid_.isInside(newPos) && bullet->getIsAlive()){
            auto newCell = grid_.getCell(newPos);
            ++it; // Ręcznie inkrementujemy iterator, jeśli nie usuwamy elementu
            bullet->setPos(newPos);
            newCell.setPlayerBullet(bullet.get());
        } else {
            bullet->setIsAlive(false);
            // Usuń wroga z wektora
            it = playerBullets_.erase(it);
        }
    }

    for (auto it = enemyBullets_.begin(); it != enemyBullets_.end(); /* pusta sekcja inkrementacji */) {
        auto &bullet = *it;
        bullet->update(deltaTime);
        sf::Vector2f displacement = bullet->getLinVel() * deltaTime; // calculate how far should move
        sf::Vector2f newPos = bullet->getPos() + displacement; // calculate new position
        auto oldCell = grid_.getCell(bullet->getPos());
        oldCell.clear_cell();
        if (grid_.isInside(newPos) && bullet->getIsAlive()){
            auto newCell = grid_.getCell(newPos);
            ++it; // Ręcznie inkrementujemy iterator, jeśli nie usuwamy elementu

            bullet->setPos(newPos);
            newCell.setEnemyBullet(bullet.get());
        } else {
            bullet->setIsAlive(false);
            // Usuń wroga z wektora
            it = enemyBullets_.erase(it);
        }
    }
}

void ProjectileManager::render(sf::RenderWindow &window) const {
    for (const auto &bullet : playerBullets_)  bullet->draw(window);
    for (const auto &bullet : enemyBullets_)   bullet->draw(window);
}

void ProjectileManager::addProjectile(const sf::Vector2f& initPos,
                                      const sf::Vector2f& initVel, const float& initRot,
                                      bool is_players, int type){
    if (is_players){
        switch (type) {
            case Projectile::bullet:
                playerBullets_.emplace_back(std::make_shared<BulletPlayer>(assetManager_.playerBulletTexture,
                                                                           initPos, initVel, initRot));

                break;
            case Projectile::missile:
                // missile
                break;

            default:
                break;

        }
    } else{
        switch (type) {
            case Projectile::bullet:
                enemyBullets_.emplace_back(std::make_shared<BulletEnemy>(assetManager_.enemyBulletTexture,
                                                                          initPos, initVel, initRot));
                break;
//            case Projectile::missile:
//                // missile
//                break;

            default:
                break;

        }
    }
}

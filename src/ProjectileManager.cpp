#include "ProjectileManager.h"

ProjectileManager::ProjectileManager(const AssetManager& assetManager, Grid& grid) :
                                     grid_(grid),
                                     assetManager_(assetManager) {
    enemyBulletSpawnOffset_ = {0, -30};
    playerBulletSpawnOffset_ = {0, -40};

}
// TODO bullet to projectile
void ProjectileManager::update(float deltaTime) {
    for (auto it = playerBullets_.begin(); it != playerBullets_.end(); /* pusta sekcja inkrementacji */) {
        auto &bullet = *it;
        bullet->update(deltaTime);
        auto oldCells = grid_.getCircleCells(bullet->getPos(),
                                             bullet->getRadius());
        sf::Vector2f displacement = bullet->getLinVel() * deltaTime; // calculate how far should move
        sf::Vector2f newPos = bullet->getPos() + displacement; // calculate new position
        auto newCells = grid_.getCircleCells(newPos, bullet->getRadius());

        if (newCells.empty()) { bullet->setIsAlive(false); } 
        else {
            for (auto &cell: newCells) {
                if (cell->hasSpaceObject()){
                    bullet->setIsAlive(false);
                    break;
                }
            }
        }

        // Usuń wroga z komórek siatki
        for (auto &cell: oldCells) cell->clear_cell();
        if (!bullet->getIsAlive()) {
            // Usuń wroga z wektora
            it = playerBullets_.erase(it);
        } else {
            ++it; // Ręcznie inkrementujemy iterator, jeśli nie usuwamy elementu
            bullet->setPos(newPos);
            for (auto &nCell : newCells) nCell->setPlayerBullet(bullet.get());
        }
    }

    for (auto it = enemyBullets_.begin(); it != enemyBullets_.end(); /* pusta sekcja inkrementacji */) {
        auto& bullet = *it;
        bullet->update(deltaTime);
        auto oldCells = grid_.getCircleCells(bullet->getPos(),
                                             bullet->getRadius());
        sf::Vector2f displacement = bullet->getLinVel() * deltaTime; // calculate how far should move
        sf::Vector2f newPos = bullet->getPos() + displacement; // calculate new position
        auto newCells = grid_.getCircleCells(newPos, bullet->getRadius());

        if (newCells.empty()){
            bullet->setIsAlive(false);
        } else{
            for (auto &cell: newCells) {
                if (cell->hasSpaceObject()){
                    bullet->setIsAlive(false);
                    break;
                }
            }
        }

        // Usuń wroga z komórek siatki
        for (auto &cell: oldCells) cell->clear_cell();
        if (!bullet->getIsAlive()) {
            // Usuń wroga z wektora
            it = enemyBullets_.erase(it);
        } else {
            ++it; // Ręcznie inkrementujemy iterator, jeśli nie usuwamy elementu
            bullet->setPos(newPos);
            for (auto &nCell : newCells) nCell->setEnemyBullet(bullet.get());
        }
    }
}

void ProjectileManager::render(sf::RenderWindow &window) const {
    for (const auto &bullet : playerBullets_)  bullet->draw(window);
    for (const auto &bullet : enemyBullets_)   bullet->draw(window);
}

void ProjectileManager::addProjectile(const sf::Vector2f& pos, float rot,
                                      bool is_players, int type){
    if (is_players){
        switch (type) {
            case 0:
                playerBullets_.emplace_back(std::make_shared<Bullet>(pos, playerBulletSpawnOffset_,
                                            rot,assetManager_.playerBulletTexture));
                break;
//            case 1:
//                // missile
//                break;

            default:
                break;

        }
    } else{
        switch (type) {
            case 0:
                enemyBullets_.emplace_back(std::make_shared<Bullet>(pos, enemyBulletSpawnOffset_,
                                            rot,assetManager_.enemyBulletTexture));
                break;
//            case 1:
//                // missile
//                break;

            default:
                break;

        }
    }

}

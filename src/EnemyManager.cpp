#include "EnemyManager.h"

EnemyManager::EnemyManager(const AssetManager& assetManager, ProjectileManager& projectileManager, Grid& grid)
                            : assetManager_(assetManager), grid_(grid), projectileManager_(projectileManager){
    shootTimeEnemy_ = 10.0f;
    spawnTime_ = 5.0f;
}
// TODO to projectiles
void EnemyManager::update(const sf::Vector2f& playerPos, float deltaTime) {
    static sf::Clock enemySpawnClock;
    sf::Time elapsed_enemy = enemySpawnClock.getElapsedTime();
    if (elapsed_enemy.asSeconds() > spawnTime_) {
       addEnemy(Enemy(randomSpawnPoint(playerPos), assetManager_.enemyTexture));
       enemySpawnClock.restart();
    }

    for (auto it = enemies_.begin(); it != enemies_.end(); /* pusta sekcja inkrementacji */) {
        auto& enemyPtr = *it;
        enemyPtr->update(playerPos, deltaTime);
        sf::Vector2f displacement = enemyPtr->getLinVel() * deltaTime; // calculate how far should move
        sf::Vector2f newPos = enemyPtr->getPos() + displacement; // calculate new position
        auto oldCell = grid_.getCell(enemyPtr->getPos());
        if (!enemyPtr->getIsAlive()) {
            // Usuń wroga z komórki siatki
            oldCell.clear_cell();
            // Usuń wroga z wektora
            it = enemies_.erase(it);
        } else if (grid_.isInside(newPos)){
            ++it; // Ręcznie inkrementujemy iterator, jeśli nie usuwamy elementu
            auto newCell = grid_.getCell(newPos);
            float angDisplacement = enemyPtr->getAngVel() * deltaTime;
            float newRot = enemyPtr->getRot() + angDisplacement;
            enemyPtr->setPos(newPos);
            enemyPtr->setRot(newRot);
            oldCell.clear_cell();
            newCell.setEnemy(enemyPtr.get());
        } else{
            ++it; // Ręcznie inkrementujemy iterator, jeśli nie usuwamy elementu
            enemyPtr->setLinVel({0.f,0.f});
        }

        // Bullets
        if (enemyPtr->canShoot(shootTimeEnemy_) and enemyPtr->getIsAlive())
            projectileManager_.addProjectile(enemyPtr->getPos(), enemyPtr->getRot(),
                                             false, ProjectileManager::bullet);

    }
}

void EnemyManager::addEnemy(const Enemy &enemy) {
    enemies_.emplace_back(std::make_shared<Enemy>(enemy));
}

void EnemyManager::render(sf::RenderWindow &window) const {
    for (const auto& enemyPtr : enemies_) enemyPtr->draw(window);
}

sf::Vector2i EnemyManager::randomSpawnPoint(const sf::Vector2f& playerPos) {
    std::random_device rd;  // (seed)
    std::mt19937 gen(rd());  // generator liczb pseudolosowych

    std::uniform_real_distribution<> distr(0, 2 * M_PI);  // rozkład jednostajny od 0 do 2*pi

    float spawnRadius = 150;  // radius of the spawn circle around the player TODO
    float spawnAngle = distr(gen);  // random angle

    // calculate the spawn point
    int _x = playerPos.x + spawnRadius * std::cos(spawnAngle);
    int _y = playerPos.y + spawnRadius * std::sin(spawnAngle);
    auto grid_size = grid_.getSizePixels();
    _x = std::min(_x, grid_size.x-1);
    _x = std::max(_x, 1);

    _y = std::min(_y, grid_size.y-1);
    _y = std::max(_y, 1);
    return {_x, _y};
}

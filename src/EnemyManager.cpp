#include "EnemyManager.h"

EnemyManager::EnemyManager(const AssetManager& assetManager, Grid& grid)
                            : assetManager_(assetManager),  grid_(grid){
    shootTimeEnemy_ = 10.0f;
    spawnTime_ = 5.0f;
    enemyBulletSpawnOffset_ = {0, -30};
}
// TODO to projectiles
void EnemyManager::update(const sf::Vector2f& playerPos, std::vector<Bullet>& bullets, float deltaTime) {
    static sf::Clock enemySpawnClock;
    sf::Time elapsed_enemy = enemySpawnClock.getElapsedTime();
    if (elapsed_enemy.asSeconds() > spawnTime_) {
       addEnemy(Enemy(randomSpawnPoint(playerPos), assetManager_.enemyTexture));
       enemySpawnClock.restart();
    }

    for (auto it = enemies_.begin(); it != enemies_.end(); /* pusta sekcja inkrementacji */) {
        auto& enemyPtr = *it;
        enemyPtr->update(playerPos, deltaTime);
        if (!enemyPtr->getIsAlive()) {
            // Usuń wroga z komórki siatki
            Cell& oldCell = grid_.getCell(enemyPtr->getPos());
            oldCell.clear_cell();

            // Usuń wroga z wektora
            it = enemies_.erase(it);
        } else {
            ++it; // Ręcznie inkrementujemy iterator, jeśli nie usuwamy elementu
            sf::Vector2f displacement = enemyPtr->getLinVel() * deltaTime; // calculate how far should move
            sf::Vector2f newPos = enemyPtr->getPos() + displacement; // calculate new position
            float angDisplacement = enemyPtr->getAngVel() * deltaTime;
            float newRot = enemyPtr->getRot() + angDisplacement;

            // check if the enemy's new bounding box collides with anything
            if (grid_.isInside(newPos)) {
                // Znajdź starą komórkę
                Cell& oldCell = grid_.getCell(enemyPtr->getPos());
                // Zaznacz starą komórkę jako pustą
                oldCell.clear_cell();

                enemyPtr->setPos(newPos);
                enemyPtr->setRot(newRot);

                // Znajdź nową komórkę
                Cell& newCell = grid_.getCell(newPos);
                // Zaznacz nową komórkę jako zajętą
                newCell.setEnemy(enemyPtr.get());
            }
                // Jeśli nowa pozycja jest poza grą lub koliduje z czymś, zatrzymaj
            else {
                sf::Vector2f _zero_vel = sf::Vector2f (0.f,0.f);
                enemyPtr->setLinVel(_zero_vel);
            }

            // Bullets
            if (enemyPtr->canShoot(shootTimeEnemy_) and enemyPtr->getIsAlive())
                bullets.emplace_back(enemyPtr->getPos(), enemyBulletSpawnOffset_,
                                     enemyPtr->getRot(),assetManager_.enemyBulletTexture);

        }
    }
}

void EnemyManager::addEnemy(const Enemy &enemy) {
    enemies_.emplace_back(std::make_shared<Enemy>(enemy));
}

void EnemyManager::render(sf::RenderWindow &window) const {
    for (const auto& enemyPtr : enemies_){
        enemyPtr->draw(window);
    }
}

sf::Vector2f EnemyManager::randomSpawnPoint(const sf::Vector2f& playerPos) {
    std::random_device rd;  // (seed)
    std::mt19937 gen(rd());  // generator liczb pseudolosowych

    std::uniform_real_distribution<> distr(0, 2 * M_PI);  // rozkład jednostajny od 0 do 2*pi
    std::uniform_real_distribution<> distrRadius(200, 600);  // rozkład jednostajny od 200 do 600

    float spawnRadius = distrRadius(gen);  // radius of the spawn circle around the player
    float spawnAngle = distr(gen);  // random angle

    // calculate the spawn point
    float _x = playerPos.x + spawnRadius * std::cos(spawnAngle);
    float _y = playerPos.y + spawnRadius * std::sin(spawnAngle);
    return {_x, _y};
}

bool EnemyManager::isCollision() {
    return false;
}

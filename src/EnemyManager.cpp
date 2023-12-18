#include "EnemyManager.h"

EnemyManager::EnemyManager(const AssetManager& assetManager, Grid& grid)
                            : assetManager_(assetManager),  grid_(grid){
    shootTimeEnemy_ = 10.0f;
    spawnTime_ = 5.0f;
}
void EnemyManager::update(const sf::Vector2f& playerPosition, float deltaTime) {
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
            Cell& oldCell = grid_.getCell(enemyPtr->getPos().x, enemyPtr->getPos().y);
            oldCell.removeEnemy(enemyPtr.get());

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
                Cell& oldCell = grid_.getCell(enemyPtr->getPos().x, enemyPtr->getPos().y);
                // Zaznacz starą komórkę jako pustą
                oldCell.removeEnemy(enemyPtr.get());

                enemyPtr->setPosition(newPos);
                enemyPtr->setRotation(newRot);

                // Znajdź nową komórkę
                Cell& newCell = grid_.getCell(newPos.x, newPos.y);
                // Zaznacz nową komórkę jako zajętą
                newCell.addEnemy(enemyPtr.get());
            }
                // Jeśli nowa pozycja jest poza grą lub koliduje z czymś, zatrzymaj
            else {
                sf::Vector2f _zero_vel = sf::Vector2f (0.f,0.f);
                enemyPtr->setLinVel(_zero_vel);
            }
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
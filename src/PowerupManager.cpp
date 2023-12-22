#include "PowerupManager.h"

PowerupManager::PowerupManager(const AssetManager &assetManager, Grid &grid) :
        grid_(grid),
        assetManager_(assetManager),
        spawnAngleRes_(10){
    spawnTime_ = 3.0f;
}

void PowerupManager::update(const sf::Vector2f& playerPos, float deltaTime) {
    static sf::Clock powerupSpawnClock;
    sf::Time elapsed_enemy = powerupSpawnClock.getElapsedTime();
    if (elapsed_enemy.asSeconds() > spawnTime_) {
        addPowerup(PowerupManager::randomSpawnPoint(playerPos), PowerupManager::acc1_2);
        powerupSpawnClock.restart();
    }

    for (auto it = powerups_.begin(); it != powerups_.end(); /* pusta sekcja inkrementacji */) {
        auto &powerup = *it;
        powerup->update(deltaTime);
        sf::Vector2f displacement = powerup->getLinVel() * deltaTime; // calculate how far should move
        sf::Vector2f newPos = powerup->getPos() + displacement; // calculate new position
        auto oldCell = grid_.getCell(powerup->getPos());
        oldCell.clear_cell();
        if (grid_.isInside(newPos) && powerup->getIsAlive()){
            auto newCell = grid_.getCell(newPos);
            ++it; // Ręcznie inkrementujemy iterator, jeśli nie usuwamy elementu
            powerup->setPos(newPos);
            newCell.setPowerup(powerup.get());
        } else {
            powerup->setIsAlive(false);
            // Usuń wroga z wektora
            it = powerups_.erase(it);
        }
    }
}

void PowerupManager::render(sf::RenderWindow &window) const {
    for (const auto &powerup : powerups_)   powerup->draw(window);
}

void PowerupManager::addPowerup(const sf::Vector2i &pos, int type) {
    switch (type) {
        case PowerupManager::acc1_2:
            powerups_.emplace_back(std::make_shared<Powerup>(pos, 90.,
                                                             assetManager_.powerupTexture));
            break;
        case PowerupManager::vel1_5:
            // missile
            break;

        default:
            break;

    }
}

sf::Vector2i PowerupManager::randomSpawnPoint(const sf::Vector2f& playerPos) {
    int randint = rand() % (spawnAngleRes_+1);
    float spawnRadius = 100;  // radius of the spawn circle around the player TODO
    float spawnAngle = ((2 * M_PI) / spawnAngleRes_) * randint;

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
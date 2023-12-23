#ifndef SPACE_SHOOTER_POWERUPMANAGER_H
#define SPACE_SHOOTER_POWERUPMANAGER_H

#include "Grid.h"
#include "Powerup.h"
#include "AssetManager.h"
#include <random>

class PowerupManager {
public:
    PowerupManager(const AssetManager& assetManager, Grid& grid);
    void update(const sf::Vector2f& playerPos, float deltaTime);
    void render(sf::RenderWindow &window) const;
    void addPowerup(const sf::Vector2i& pos, int type);

    std::vector<std::shared_ptr<Powerup>> powerups_;
private:
    const AssetManager& assetManager_;
    Grid& grid_;
    float spawnTime_;
    const int spawnAngleRes_;
    std::vector<float> spawnAngles_;
    sf::Vector2i randomSpawnPoint(const sf::Vector2f& playerPos);
};


#endif //SPACE_SHOOTER_POWERUPMANAGER_H

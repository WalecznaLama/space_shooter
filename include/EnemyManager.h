//
// Created by rav on 08.08.23.
//

#ifndef SPACE_SHOOTER_ENEMYMANAGER_H
#define SPACE_SHOOTER_ENEMYMANAGER_H

#include "Enemy.h"
#include "AssetManager.h"
#include "Grid.h"
#include "Bullet.h"

class EnemyManager {
public:
    EnemyManager(const AssetManager& assetManager, Grid& grid);
    void update(const sf::Vector2f&  playerPos, std::vector<Bullet>& bullets, float deltaTime);
    void addEnemy(const Enemy& enemy);
    void render(sf::RenderWindow &window) const;
    bool isCollision();
private:
    const AssetManager& assetManager_;
    Grid& grid_;
    float shootTimeEnemy_;
    float spawnTime_;
    sf::Vector2f enemyBulletSpawnOffset_;
    std::vector<std::shared_ptr<Enemy>> enemies_;

    static sf::Vector2f randomSpawnPoint(const sf::Vector2f& playerPos);
};


#endif //SPACE_SHOOTER_ENEMYMANAGER_H

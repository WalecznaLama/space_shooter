#ifndef SPACE_SHOOTER_ENEMYMANAGER_H
#define SPACE_SHOOTER_ENEMYMANAGER_H

#include "Enemy.h"
#include "ProjectileManager.h"
#include "Grid.h"
#include "Bullet.h"

class EnemyManager {
public:
    EnemyManager(const AssetManager& assetManager, ProjectileManager& projectileManager, Grid& grid);
    void update(const sf::Vector2f&  playerPos, float deltaTime);
    void addEnemy(const Enemy& enemy);
    void render(sf::RenderWindow &window) const;
    bool isCollision();

private:
    const AssetManager& assetManager_;
    ProjectileManager& projectileManager_;
    Grid& grid_;
    float shootTimeEnemy_;
    float spawnTime_;
    std::vector<std::shared_ptr<Enemy>> enemies_;

    static sf::Vector2i randomSpawnPoint(const sf::Vector2f& playerPos);
};


#endif //SPACE_SHOOTER_ENEMYMANAGER_H

#ifndef SPACE_SHOOTER_PROJECTILEMANAGER_H
#define SPACE_SHOOTER_PROJECTILEMANAGER_H

#include "Grid.h"
#include "Bullet.h"
#include "AssetManager.h"

class ProjectileManager {
public:
    ProjectileManager(const AssetManager& assetManager, Grid& grid);
    void update(float deltaTime);
    void render(sf::RenderWindow &window) const;
    enum projectileType {bullet, missile};
    void addProjectile(const sf::Vector2f& pos, float rot, bool is_players, int type); // ToDO enum

private:
    const AssetManager& assetManager_;
    Grid& grid_;
    std::vector<std::shared_ptr<Bullet>> playerBullets_;
    std::vector<std::shared_ptr<Bullet>> enemyBullets_;
    sf::Vector2f enemyBulletSpawnOffset_;
    sf::Vector2f playerBulletSpawnOffset_;
};


#endif //SPACE_SHOOTER_PROJECTILEMANAGER_H

#ifndef SPACE_SHOOTER_PROJECTILEMANAGER_H
#define SPACE_SHOOTER_PROJECTILEMANAGER_H

#include "Grid.h"
#include "Projectile/Projectile.h"
#include "AssetManager.h"

class ProjectileManager {
public:
    ProjectileManager(const AssetManager& assetManager, Grid& grid);
    void update(float deltaTime);
    void render(sf::RenderWindow &window) const;
    void addProjectile(const sf::Vector2f& initPos,
                       const sf::Vector2f& initVel, const float& initRot, bool is_players, int type);

    std::vector<std::shared_ptr<BulletPlayer>> playerBullets_;
    std::vector<std::shared_ptr<BulletEnemy>> enemyBullets_;
private:
    const AssetManager& assetManager_;
    Grid& grid_;
};


#endif //SPACE_SHOOTER_PROJECTILEMANAGER_H

#ifndef SPACE_SHOOTER_PLAYERMANAGER_H
#define SPACE_SHOOTER_PLAYERMANAGER_H

#include "Player.h"
#include "ProjectileManager.h"
#include "Grid.h"
#include "Bullet.h"

class PlayerManager {
public:
    PlayerManager(const AssetManager& assetManager, ProjectileManager& projectileManager, Grid& grid);
    void update(const sf::Vector2f &spaceObjectsNetForce, float deltaTime);
    void render(sf::RenderWindow &window) const;

    std::shared_ptr<Player> player_;

private:
    const AssetManager& assetManager_;
    ProjectileManager& projectileManager_;
    Grid& grid_;
    float shootTimePlayer_;
    sf::Clock collisionTimer_;
};

#endif //SPACE_SHOOTER_PLAYERMANAGER_H

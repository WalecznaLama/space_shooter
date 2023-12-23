#ifndef SPACE_SHOOTER_SPACEOBJECTMANAGER_H
#define SPACE_SHOOTER_SPACEOBJECTMANAGER_H

#include "Grid.h"
#include "Planet.h"
#include "AssetManager.h"

class SpaceObjectManager {
public:
    SpaceObjectManager(const AssetManager& assetManager, Grid& grid);
    sf::Vector2f update(const sf::Vector2f&  playerPos);
    void render(sf::RenderWindow &window) const;
    enum spaceObjectType {planet, black_hole};
    void addSpaceObject(const sf::Vector2f& pos, const sf::Vector2f& vel, int type, int radius, float rot=0.f);

    std::vector<std::shared_ptr<SpaceObject>> spaceObjects_;
private:
    const AssetManager& assetManager_;
    Grid& grid_;
};


#endif //SPACE_SHOOTER_SPACEOBJECTMANAGER_H

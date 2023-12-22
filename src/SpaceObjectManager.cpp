#include "SpaceObjectManager.h"

SpaceObjectManager::SpaceObjectManager(const AssetManager &assetManager, Grid &grid) :
        grid_(grid),
        assetManager_(assetManager) {

}

sf::Vector2f SpaceObjectManager::update(const sf::Vector2f& playerPos) {
    sf::Vector2f spaceObjectsNetForce = {0.f, 0.f};
    for (const auto& spaceObjectPtr : spaceObjects_){
        spaceObjectPtr->update();
        sf::Vector2f direction = spaceObjectPtr->getPos() - playerPos ;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance == 0.0f) continue; // Aby uniknąć dzielenia przez zero

        // Normalizacja wektora kierunku (daje wektor o długości 1 w kierunku planet)
        direction /= distance;
        // Obliczenie siły przy użyciu prawa grawitacji uniwersalnej
        float forceMagnitude = SpaceObject::G_ * spaceObjectPtr->getMass() / (distance * distance);

        // Dodajemy siłę do wypadkowej siły
        spaceObjectsNetForce += direction * forceMagnitude;
    }
    return spaceObjectsNetForce;
}

void SpaceObjectManager::render(sf::RenderWindow &window) const {
    for (const auto &spaceObject : spaceObjects_)  spaceObject->draw(window);

}

void SpaceObjectManager::addSpaceObject(const sf::Vector2f &pos, const sf::Vector2f& vel,
                                        int type, int radius, float rot) {
    spaceObjects_.emplace_back(std::make_shared<Planet>(assetManager_.planetTexture, pos, vel, rot, radius));
}

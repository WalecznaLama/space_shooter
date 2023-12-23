#include "PlayerManager.h"

PlayerManager::PlayerManager(const AssetManager &assetManager, ProjectileManager &projectileManager, Grid &grid)
    : player_(std::make_shared<Player>(sf::Vector2f(1500, 1500), // todo
                                       assetManager.playerTextures_)),
    assetManager_(assetManager), grid_(grid), projectileManager_(projectileManager) {
    shootTimePlayer_ = 0.2f;

    }

void PlayerManager::update(const sf::Vector2f &spaceObjectsNetForce, float deltaTime) {
    player_->update(deltaTime, spaceObjectsNetForce);
    sf::Vector2f linDisplacement = player_->getLinVel() * deltaTime; // calculate how far the player should move
    sf::Vector2f newPos = player_->getPos() + linDisplacement; // calculate the player's new position

    if (grid_.isInside(newPos)){
        auto newCell = grid_.getCell(newPos);
        auto oldCell = grid_.getCell(player_->getPos());
        float angDisplacement = player_->getAngVel() * deltaTime;
        float newRot = player_->getRot() + angDisplacement;

        // Ustaw nową pozycję gracza
        player_->setPos(newPos);
        player_->setRot(newRot);

        oldCell.clear_cell();
        newCell.setPlayer(player_.get());

    } else{
        // Jeśli nowa pozycja jest poza grą lub koliduje z czymś, zatrzymaj gracza
        player_->setLinVel({0.f, 0.f});
    }

    // Shoot on Space and A
    bool _user_shoot = (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
                        || sf::Joystick::isButtonPressed(0, 0));
    if (_user_shoot && player_->canShoot(shootTimePlayer_))
        projectileManager_.addProjectile(player_->getPos(), player_->getRot(),
                                         true, ProjectileManager::bullet);
}

void PlayerManager::render(sf::RenderWindow &window) const {
    player_->draw(window);
}

#include "PlayerManager.h"

PlayerManager::PlayerManager(const AssetManager &assetManager, ProjectileManager &projectileManager, Grid &grid)
    : player_(std::make_shared<Player>(sf::Vector2f(1500, 1500), assetManager.playerTextures_)),
    assetManager_(assetManager), grid_(grid), projectileManager_(projectileManager) {
    shootTimePlayer_ = 0.2f;
    }

void PlayerManager::update(const sf::Vector2f &spaceObjectsNetForce, float deltaTime) {
    player_->update(deltaTime, spaceObjectsNetForce);
    sf::Vector2f linDisplacement = player_->getLinVel() * deltaTime; // calculate how far the player should move
    sf::Vector2f newPos = player_->getPos() + linDisplacement; // calculate the player's new position

    bool collidesWithSomething = false;
    auto newCells = grid_.getCircleCells(newPos, player_->getRadius());
    auto oldCells = grid_.getCircleCells(player_->getPos(),
                                         int(player_->getRadius()));

    for (auto &cell : oldCells){
        if (cell->hasEnemyBullet()){
            int damage = 2; // TODO int damage = grid_.getCell(newPos).getEnemyBullet().get_damage()
            auto bulletCell = cell->getEnemyBullet();
            bulletCell->setIsAlive(false);
            player_->setDamage(damage);
            break;
        }
        if (cell->hasEnemy() && collisionTimer_.getElapsedTime().asMilliseconds() > 1000){ // TODO const
            collidesWithSomething = true;
            int damage = 1;
            auto enemyCell = cell->getEnemy();
            enemyCell->setDamage(damage);
            collisionTimer_.restart();
            break;
        }
    }

    if (newCells.empty() || collidesWithSomething) {
        // Jeśli nowa pozycja jest poza grą lub koliduje z czymś, zatrzymaj gracza
        player_->setLinVel({0.f, 0.f});
    } else {
        float angDisplacement = player_->getAngVel() * deltaTime;
        float newRot = player_->getRot() + angDisplacement;

        // Ustaw nową pozycję gracza
        player_->setPos(newPos);
        player_->setRot(newRot);

        for (auto &oCell : oldCells) oCell->clear_cell();
        for (auto &nCell : newCells) nCell->setPlayer(player_.get());
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

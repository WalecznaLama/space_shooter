#include "Game.h"

// TODO grid
Game::Game()
        : window_("Space Shooter", sf::Vector2u(1280, 720)), // Initialize GameWindow with a title and size
          grid_(3000, 3000),
          assets_(),
          player_(std::make_shared<Player>(sf::Vector2f(1500, 1500), assets_.playerTextures_)),
          enemyManager_(assets_, grid_)
{
    setGui();

    playerBulletSpawnOffset_ = {0, -40};


    shootTimePlayer_ = 0.2f;
    shootTimeEnemy_ = 10.0f;

    sf::Vector2f vel = {0., 0.};
    sf::Vector2f pos = {1700., 1700.};
    spaceObjects_.emplace_back(std::make_shared<Planet>(assets_.planetTexture, pos, vel,
                                                        0.0, 200.));

    powerups_.emplace_back(pos, 0., assets_.powerupTexture);

    cameraAcc_ = 0.01f;

    killCounter_ = 0;
}

void Game::run() {
    while (window_.isOpen()) {
        window_.processEvents();
        update();
        render();
    }
}

void Game::update() {
    float elapsed = updateClock_.getElapsedTime().asSeconds();

    updatePlayer(elapsed);
    enemyManager_.update(player_->getPos(), enemyBullets_, elapsed);
    updateGui(elapsed);
    updateSpaceObjects(elapsed);

    updateBullets(elapsed);
    updatePowerups(elapsed);

    calculateCameraPos();
    window_.updateView(cameraPos_);
    if (!player_->getIsAlive()) gameOver();
    updateClock_.restart();
}

void Game::render() {
    window_.clear();
    window_.draw(backgroundSprite_);  // draw the background
    for (const Powerup& powerup : powerups_)     powerup.draw(window_.getRenderWindow());
    for (const Bullet& bullet : playerBullets_)  bullet.draw(window_.getRenderWindow());
    for (const Bullet& bullet : enemyBullets_)   bullet.draw(window_.getRenderWindow());
//    for (const Enemy& enemy : enemies_)          enemy.draw(window_.getRenderWindow());
    enemyManager_.render(window_.getRenderWindow());

    for (const auto& spaceObjectPtr : spaceObjects_)
        window_.draw(spaceObjectPtr->getSprite());

    player_->draw(window_.getRenderWindow());

    window_.setUiView();
    window_.draw(fpsText_);  // draw the fps text
    window_.draw(killCounterText_);  // draw the killCounter text
    window_.draw(debugText_);
    window_.draw(heartSprite_);
    window_.display();
}

void Game::gameOver() {
    finalScreenText_.setString("Game Over!\nFinal Score: " + std::to_string(killCounter_));
    finalScreenText_.setPosition(cameraPos_);
    while (window_.isOpen()) {
        window_.processEvents();
        window_.clear();
        window_.draw(finalScreenText_);
        window_.display();
    }
}

void Game::updateBullets(float deltaTime) {
    for (int i = playerBullets_.size() - 1; i >= 0; --i) {
        Bullet& bullet = playerBullets_[i];
        bullet.update(deltaTime);

        sf::Vector2f linDisplacement = bullet.getLinVel() * deltaTime;
        sf::Vector2f newPos = bullet.getPos() + linDisplacement;
        bullet.setPos(newPos);
        if (!grid_.isInside(bullet.getPos()) or !bullet.getIsAlive())
            playerBullets_.erase(playerBullets_.begin() + i);
    }

    for (int i = enemyBullets_.size() - 1; i >= 0; --i) {
        Bullet &bullet = enemyBullets_[i];
        bullet.update(deltaTime);
        sf::Vector2f linDisplacement = bullet.getLinVel() * deltaTime;
        sf::Vector2f newPos = bullet.getPos() + linDisplacement;
        bullet.setPos(newPos);
        if (!grid_.isInside(bullet.getPos()) or !bullet.getIsAlive())
            enemyBullets_.erase(enemyBullets_.begin() + i);
    }
}

void Game::updatePowerups(float deltaTime) {
//    static sf::Clock powerupSpawnClock;
//    sf::Time elapsed_enemy = powerupSpawnClock.getElapsedTime();
//    if (elapsed_enemy.asSeconds() >= 3.0f) {  // every 3 seconds spawn enemy
//        // TODO
//        powerups_.emplace_back(randomSpawnPoint(), 90., assets_.powerupTexture);
//        powerupSpawnClock.restart();
//    }

    for (int i = powerups_.size() - 1; i >= 0; --i) {
        Powerup& powerup = powerups_[i];
        powerup.update(deltaTime);

        sf::Vector2f linDisplacement = powerup.getLinVel() * deltaTime;
        sf::Vector2f newPos = powerup.getPos() + linDisplacement;
        float angDisplacement = powerup.getAngVel() * deltaTime;
        float newRot = powerup.getRot() + angDisplacement;
        powerup.setPos(newPos);
        powerup.setRot(newRot);

        sf::Vector2f diff = player_->getPos() - powerup.getPos();
        float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

        float _sum_radius = player_->getRadius() + powerup.getRadius();
        if (distance < _sum_radius) {
            player_->setLinAcc( player_->getLinAcc() * 1.2 );
            powerup.setIsAlive(false);
            break;
        }

        // remove off screen
        if (!grid_.isInside(powerup.getPos()) or !powerup.getIsAlive())
            powerups_.erase(powerups_.begin() + i);
    }
}

void Game::updatePlayer(float deltaTime) {
    player_->update(deltaTime, spaceObjectsNetForce_);

    // check if the player's new bounding box collides with anything
    bool collidesWithSomething = getPlayerCollision();

    sf::Vector2f linDisplacement = player_->getLinVel() * deltaTime; // calculate how far the player should move
    sf::Vector2f newPos = player_->getPos() + linDisplacement; // calculate the player's new position
    float angDisplacement = player_->getAngVel() * deltaTime;
    float newRot = player_->getRot() + angDisplacement;

    // Jeśli nowa pozycja jest wewnątrz gry i nie koliduje z niczym
//    if (grid_.isInside(newPosition) && !grid_.getCell(newPosition.x, newPosition.y).isOccupiedEnemy()) {
    if (grid_.isInside(newPos) && !collidesWithSomething) {
        // Znajdź starą komórkę, w której znajduje się gracz
        Cell& oldCell = grid_.getCell(player_->getPos().x, player_->getPos().y);
        // Zaznacz starą komórkę jako pustą
        oldCell.setPlayer(nullptr);

        // Ustaw nową pozycję gracza
        player_->setPos(newPos);
        player_->setRot(newRot);

        // Znajdź nową komórkę, w której znajduje się gracz
        Cell& newCell = grid_.getCell(newPos.x, newPos.y);
        // Zaznacz nową komórkę jako zajętą przez gracza
        newCell.setPlayer(player_.get());
    }
        // Jeśli nowa pozycja jest poza grą lub koliduje z czymś, zatrzymaj gracza
    else {
        sf::Vector2f _zero_vel = sf::Vector2f (0.f,0.f);
        player_->setLinVel(_zero_vel);
    }

    // Shoot on Space and A
    bool _user_shoot = (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
                        || sf::Joystick::isButtonPressed(0, 0));
    if (_user_shoot && player_->canShoot(shootTimePlayer_))
        playerBullets_.emplace_back(player_->getPos(),
                                    playerBulletSpawnOffset_,
                                    player_->getRot(),
                                    assets_.playerBulletTexture);
}

//void Game::updateEnemies(float deltaTime) {
//    static sf::Clock enemySpawnClock;
//    sf::Time elapsed_enemy = enemySpawnClock.getElapsedTime();
//    if (elapsed_enemy.asSeconds() >= 5.0f) {  // every 5 seconds spawn enemy
//        enemies_.emplace_back(randomSpawnPoint(), assets_.enemyTexture);
//        enemySpawnClock.restart();
//    }
//
//    for (int i = enemies_.size() - 1; i >= 0; --i) {
//        Enemy& enemy = enemies_[i];
//
//        enemy.update(player_->getPos(), deltaTime);
//
//        sf::Vector2f displacement = enemy.getLinVel() * deltaTime; // calculate how far should move
//        sf::Vector2f newPos = enemy.getPos() + displacement; // calculate new position
//        float angDisplacement = enemy.getAngVel() * deltaTime;
//        float newRot = enemy.getRot() + angDisplacement;
//
//        // check if the enemy's new bounding box collides with anything
//        bool collidesWithSomething = false;
//
//        for (auto& bullet : playerBullets_) {
//            // Oblicz odległość między graczem a wrogiem
//            sf::Vector2f diff = bullet.getPos() - enemy.getPos();
//            float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
//
//            // Sprawdź, czy odległość jest mniejsza lub równa sumie promieni
//            float _sum_radius = bullet.getRadius() + enemy.getRadius();
//            if (distance < _sum_radius) {
//                collidesWithSomething = true;
//                enemy.setIsAlive(false);
//                bullet.setIsAlive(false);
//                killCounter_++;
//                break;
//            }
//        }
//
//        // if the enemy's new position is inside the game area and doesn't collide with anything, move the player
//        if (!collidesWithSomething && grid_.isInside(newPos.x, newPos.y)) {
//            enemy.setPos(newPos);
//            enemy.setRot(newRot);
//        }
//        // Bullets
//        if (enemy.canShoot(shootTimeEnemy_) and enemy.getIsAlive())
//            enemyBullets_.emplace_back(enemy.getPos(), enemyBulletSpawnOffset_,
//                                       enemy.getRot(),assets_.enemyBulletTexture);
//
//        if (!enemy.getIsAlive()) enemies_.erase(enemies_.begin() + i);
//    }
//}

void Game::updateGui(float deltaTime) {
    float fps = 1.f / deltaTime;
    fpsText_.setString("FPS: " + std::to_string(static_cast<int>(fps)));
    killCounterText_.setString("Score: " + std::to_string(killCounter_));
//    debugText_.setString("X: " + std::to_string(spaceObjectsNetForce_.x) + '\n' +
//                         "Y: " + std::to_string(spaceObjectsNetForce_.y));

//    debugText_.setString("X: " + std::to_string( powerups_[0].getAngAcc()));

    float hp_percent = player_->getHp() * 1. / player_->getMaxHp();
    heartSprite_.setTextureRect(sf::IntRect(0, 0,
                                            heartSprite_.getTexture()->getSize().x * hp_percent,
                                            heartSprite_.getTexture()->getSize().y));
}

sf::Vector2f Game::randomSpawnPoint() {
    std::random_device rd;  // (seed)
    std::mt19937 gen(rd());  // generator liczb pseudolosowych

    std::uniform_real_distribution<> distr(0, 2 * M_PI);  // rozkład jednostajny od 0 do 2*pi
    std::uniform_real_distribution<> distrRadius(200, 600);  // rozkład jednostajny od 200 do 600

    float spawnRadius = distrRadius(gen);  // radius of the spawn circle around the player
    float spawnAngle = distr(gen);  // random angle

    // calculate the spawn point
    float _x = player_->getPos().x + spawnRadius * std::cos(spawnAngle);
    float _y = player_->getPos().y + spawnRadius * std::sin(spawnAngle);
    return {_x, _y};
}

bool Game::getPlayerCollision() {
    bool collidesWithSomething = false;

    for (const auto& spaceObjectPtr : spaceObjects_){
        sf::Vector2f diff = player_->getPos() - spaceObjectPtr->getPos();
        float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

        float _sum_radius = player_->getRadius() + spaceObjectPtr->getRadius();
        if (distance < _sum_radius) {
            collidesWithSomething = true;
            break;
        }
    }

    for (auto& enemy : enemies_) {
        // Oblicz odległość między graczem a wrogiem
        sf::Vector2f diff = player_->getPos() - enemy.getPos();
        float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

        // Sprawdź, czy odległość jest mniejsza lub równa sumie promieni kara co sekunde
        float _sum_radius = player_->getRadius() + enemy.getRadius();
        if (distance < _sum_radius && collisionTimer_.getElapsedTime().asSeconds() > 1.0f) {
            collidesWithSomething = true;
            enemy.setDamage(1);
            player_->setDamage(1);
            collisionTimer_.restart();
            break;
        }
    }

    // Check collision with enemy bullets
    if (!collidesWithSomething) {
        for (auto& bullet : enemyBullets_) {
            // Oblicz odległość między graczem a wrogiem
            sf::Vector2f diff = player_->getPos() - bullet.getPos();
            float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

            float _sum_radius = player_->getRadius() + bullet.getRadius();
            if (distance < _sum_radius) {
                collidesWithSomething = true;
                player_->setDamage(1);
                bullet.setIsAlive(false);
                break;
            }
        }
    }

    return collidesWithSomething;
}


void Game::calculateCameraPos() {
    sf::Vector2f direction = player_->getPos() - cameraPos_;
    // move the camera towards the player with a certain acceleration
    cameraPos_ += direction * cameraAcc_;
}

void Game::updateSpaceObjects(float deltaTime) {
    spaceObjectsNetForce_ = {0.f, 0.f};
    for (const auto& spaceObjectPtr : spaceObjects_){
        spaceObjectPtr->update();
        sf::Vector2f direction = spaceObjectPtr->getPos() - player_->getPos() ;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance == 0.0f) continue; // Aby uniknąć dzielenia przez zero

        // Normalizacja wektora kierunku (daje wektor o długości 1 w kierunku planet)
        direction /= distance;
        // Obliczenie siły przy użyciu prawa grawitacji uniwersalnej
        float forceMagnitude = SpaceObject::G_ * player_->getMass() * spaceObjectPtr->getMass() / (distance * distance);

        // Dodajemy siłę do wypadkowej siły
        spaceObjectsNetForce_ += direction * forceMagnitude;
    }
}

void Game::setGui() {
    cameraPos_ = player_->getPos();

    // set the texture to the sprite_
    backgroundSprite_.setTexture(assets_.backgroundTexture);
    heartSprite_.setTexture(assets_.heartTexture);
    heartSprite_.scale(.5, .5);
    heartSprite_.setPosition(10, window_.getSize().y - 100);

    // set up fps and killCounter text
    fpsText_.setFont(assets_.font);
    fpsText_.setCharacterSize(20);  // in pixels
    fpsText_.setFillColor(sf::Color::White);
    fpsText_.setPosition(10, 10);  // top left corner

    killCounterText_.setFont(assets_.font);
    killCounterText_.setCharacterSize(20);  // in pixels
    killCounterText_.setFillColor(sf::Color::Red);
    killCounterText_.setPosition(10, window_.getSize().y - 50);  // bottom left corner

    finalScreenText_.setFont(assets_.font);
    finalScreenText_.setCharacterSize(24);
    finalScreenText_.setFillColor(sf::Color::Red);
    finalScreenText_.setStyle(sf::Text::Bold);

    sf::FloatRect textRect = finalScreenText_.getLocalBounds();
    finalScreenText_.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);

    debugText_.setFont(assets_.font);
    debugText_.setCharacterSize(20);  // in pixels
    debugText_.setFillColor(sf::Color::Red);
    debugText_.setPosition(10,  300);
}

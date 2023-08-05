#include "Game.h"

// TODO  black holes!/w gravity,
Game::Game()
        : window_("Space Shooter", sf::Vector2u(1280, 720)), // Initialize GameWindow with a title and size
          grid_(3000, 3000),
          assets_(),
          player_(std::make_shared<Player>(sf::Vector2f(1500, 1500), assets_.playerTextures_))
{

    cameraPosition_ = player_->getPosition();
    // set the texture to the sprite_
    backgroundSprite_.setTexture(assets_.backgroundTexture);

    // set up fps and killCounter text
    fpsText_.setFont(assets_.font);
    fpsText_.setCharacterSize(20);  // in pixels
    fpsText_.setFillColor(sf::Color::White);
    fpsText_.setPosition(10, 10);  // top left corner

    killCounterText_.setFont(assets_.font);
    killCounterText_.setCharacterSize(40);  // in pixels
    killCounterText_.setFillColor(sf::Color::Red);
    killCounterText_.setPosition(10, window_.getSize().y - 50);  // bottom left corner

    player_bullet_speed_ = 1.8f;
    enemy_bullet_speed_ = 1.2f;
    powerup_speed_ = 0.4f;
    shoot_time_player_ = 0.2f;
    shoot_time_enemy_ = 20.0f;
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
    updateEnemies(elapsed);
    updateTexts(elapsed);

    updateBullets();
    updatePowerups();

//    cameraPosition_ = player_->getPosition() ;
    calculateCameraPosition();
    window_.updateView(cameraPosition_);
    if (!player_->getIsAlive()) gameOver();

    updateClock_.restart();
}

void Game::render() {
    window_.clear();
    window_.draw(backgroundSprite_);  // draw the background
    for (const Powerup& powerup : powerups_)     powerup.draw(window_.getRenderWindow());
    for (const Bullet& bullet : playerBullets_)  bullet.draw(window_.getRenderWindow());
    for (const Bullet& bullet : enemyBullets_)   bullet.draw(window_.getRenderWindow());
    for (const Enemy& enemy : enemies_)          enemy.draw(window_.getRenderWindow());
    player_->draw(window_.getRenderWindow());

    window_.setUiView();
    window_.draw(fpsText_);  // draw the fps text
    window_.draw(killCounterText_);  // draw the killCounter text
    window_.display();
}

void Game::gameOver() {
    sf::Text gameOverText;
    gameOverText.setFont(assets_.font);
    gameOverText.setString("Game Over!\nFinal Score: " + std::to_string(kill_counter_));
    gameOverText.setCharacterSize(24);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);

    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    gameOverText.setPosition(cameraPosition_);

    while (window_.isOpen()) {
        window_.processEvents();
        window_.clear();
        window_.draw(gameOverText);
        window_.display();
    }
}

void Game::updateBullets() {
    for (int i = playerBullets_.size() - 1; i >= 0; --i) {
        Bullet& bullet = playerBullets_[i];
        bullet.update(player_bullet_speed_);
        if (!grid_.isInside(bullet.getPosition()) or !bullet.getIsAlive())   playerBullets_.erase(playerBullets_.begin() + i);
    }

    for (int i = enemyBullets_.size() - 1; i >= 0; --i) {
        Bullet &bullet = enemyBullets_[i];
        bullet.update(enemy_bullet_speed_);
        if (!grid_.isInside(bullet.getPosition()) or !bullet.getIsAlive()) enemyBullets_.erase(enemyBullets_.begin() + i);
    }
}

void Game::updatePowerups() {
    static sf::Clock powerupSpawnClock;
    sf::Time elapsed_enemy = powerupSpawnClock.getElapsedTime();
    if (elapsed_enemy.asSeconds() >= 3.0f) {  // every 3 seconds spawn enemy
        powerups_.emplace_back(window_.getSize(), assets_.powerupTexture);
        powerupSpawnClock.restart();
    }

    for (int i = powerups_.size() - 1; i >= 0; --i) {
        Powerup& powerup = powerups_[i];
        powerup.update(powerup_speed_);
        // remove off screen
        if (grid_.isInside(powerup.getPosition())) { powerups_.erase(powerups_.begin() + i); }
    }
}

// TODO add HP
void Game::updatePlayer(float deltaTime) {
    player_->update(deltaTime);

    // check if the player's new bounding box collides with anything
    checkPlayerCollision();

    sf::Vector2f linDisplacement = player_->getLinearVelocity() * deltaTime; // calculate how far the player should move
    sf::Vector2f newPosition = player_->getPosition() + linDisplacement; // calculate the player's new position
    float angDisplacement = player_->getAngularVelocity() * deltaTime;
    float newRotation = player_->getRotation() + angDisplacement;

    // Jeśli nowa pozycja jest wewnątrz gry i nie koliduje z niczym
    if (grid_.isInside(newPosition) && !grid_.getCell(newPosition.x, newPosition.y).isOccupiedEnemy()) {
        // Znajdź starą komórkę, w której znajduje się gracz
        Cell& oldCell = grid_.getCell(player_->getPosition().x, player_->getPosition().y);
        // Zaznacz starą komórkę jako pustą
        oldCell.setPlayer(nullptr);

        // Ustaw nową pozycję gracza
        player_->setPosition(newPosition);
        player_->setRotation(newRotation);

        // Znajdź nową komórkę, w której znajduje się gracz
        Cell& newCell = grid_.getCell(newPosition.x, newPosition.y);
        // Zaznacz nową komórkę jako zajętą przez gracza
        newCell.setPlayer(player_.get());
    }
        // Jeśli nowa pozycja jest poza grą lub koliduje z czymś, zatrzymaj gracza
    else {
        sf::Vector2f _zero_velocity = sf::Vector2f (0.f,0.f);
        player_->setVelocity(_zero_velocity);
    }

    // Shoot on Space and A
    bool _user_shoot = (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
                        || sf::Joystick::isButtonPressed(0, 0));

    if (_user_shoot && player_->canShoot(shoot_time_player_))
        playerBullets_.emplace_back(player_->getPosition(),
                                    assets_.playerBulletTexture,player_->getRotation());

}

void Game::updateEnemies(float deltaTime) {
    static sf::Clock enemySpawnClock;
    sf::Time elapsed_enemy = enemySpawnClock.getElapsedTime();
    if (elapsed_enemy.asSeconds() >= 5.0f) {  // every 5 seconds spawn enemy
        enemies_.emplace_back(randomSpawnPoint(), assets_.enemyTexture);
        enemySpawnClock.restart();
    }

    for (int i = enemies_.size() - 1; i >= 0; --i) {
        Enemy& enemy = enemies_[i];

        enemy.update(player_->getPosition(), deltaTime);

        sf::Vector2f displacement = enemy.getLinearVelocity() * deltaTime; // calculate how far should move
        sf::Vector2f newPosition = enemy.getPosition() + displacement; // calculate new position
        float angDisplacement = enemy.getAngularVelocity() * deltaTime;
        float newRotation = enemy.getRotation() + angDisplacement;

        // check if the enemy's new bounding box collides with anything
        bool collidesWithSomething = false;

        for (auto& bullet : playerBullets_) {
            // Oblicz odległość między graczem a wrogiem
            sf::Vector2f diff = bullet.getPosition() - enemy.getPosition();
            float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

            // Sprawdź, czy odległość jest mniejsza lub równa sumie promieni
            float _sum_radius = bullet.getRadius() + enemy.getRadius();
            if (distance < _sum_radius) {
                collidesWithSomething = true;
                enemy.setIsAlive(false);
                bullet.setIsAlive(false);
                kill_counter_++;
                break;
            }
        }

        // if the enemy's new position is inside the game area and doesn't collide with anything, move the player
        if (!collidesWithSomething && grid_.isInside(newPosition.x, newPosition.y)) {
            enemy.setPosition(newPosition);
            enemy.setRotation(newRotation);
        }

        if (enemy.canShoot(shoot_time_enemy_) and enemy.getIsAlive())
            enemyBullets_.emplace_back(enemy.getPosition(),
                                       assets_.enemyBulletTexture,enemy.getSprite().getRotation());

        if (!enemy.getIsAlive()) enemies_.erase(enemies_.begin() + i);
    }
}

void Game::updateTexts(float deltaTime) {
    float fps = 1.f / deltaTime;
    fpsText_.setString("FPS: " + std::to_string(static_cast<int>(fps)));
    killCounterText_.setString("Score: " + std::to_string(kill_counter_));
//    killCounterText_.setString("Score: " + std::to_string(playerBullets_.size()));
}

sf::Vector2f Game::randomSpawnPoint() {
    std::random_device rd;  // (seed)
    std::mt19937 gen(rd());  // generator liczb pseudolosowych

    std::uniform_real_distribution<> distr(0, 2 * M_PI);  // rozkład jednostajny od 0 do 2*pi
    std::uniform_real_distribution<> distrRadius(200, 600);  // rozkład jednostajny od 0 do 600

    float spawnRadius = distrRadius(gen);  // radius of the spawn circle around the player
    float spawnAngle = distr(gen);  // random angle

    // calculate the spawn point
    float _x = player_->getPosition().x + spawnRadius * std::cos(spawnAngle);
    float _y = player_->getPosition().y + spawnRadius * std::sin(spawnAngle);
    return {_x, _y};
}

void Game::checkPlayerCollision() {
    bool collidesWithSomething = false;

    for (auto& enemy : enemies_) {
        // Oblicz odległość między graczem a wrogiem
        sf::Vector2f diff = player_->getPosition() - enemy.getPosition();
        float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

        // Sprawdź, czy odległość jest mniejsza lub równa sumie promieni kara co sekunde
        float _sum_radius = player_->getRadius() + enemy.getRadius();
        if (distance < _sum_radius && collisionTimer_.getElapsedTime().asSeconds() > 1.0f) {
            collidesWithSomething = true;
//            player_->setIsAlive(false);
//            enemy.setIsAlive(false);
            lives_--;
            collisionTimer_.restart();
            break;
        }
    }

    // Check collision with enemy bullets
    if (!collidesWithSomething) {
        for (auto& bullet : enemyBullets_) {
            // Oblicz odległość między graczem a wrogiem
            sf::Vector2f diff = player_->getPosition() - bullet.getPosition();
            float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

            float _sum_radius = player_->getRadius() + bullet.getRadius();
            if (distance < _sum_radius) {
                collidesWithSomething = true;
                lives_--;
                bullet.setIsAlive(false);
                break;
            }
        }
    }

    // Check collision with powerups
    if (!collidesWithSomething) {
        for (auto& powerup : powerups_) {
            sf::Vector2f diff = player_->getPosition() - powerup.getPosition();
            float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);

            float _sum_radius = player_->getRadius() + powerup.getRadius();
            if (distance < _sum_radius) {
                collidesWithSomething = true;
                lives_++;
                player_->multiplyLinearAcc(1.2);
                powerup.setIsAlive(false);
                break;
            }
        }
    }
    if (lives_ < 1) player_->setIsAlive(false);
}

void Game::calculateCameraPosition() {
    sf::Vector2f direction = player_->getPosition() - cameraPosition_;

    // move the camera towards the player with a certain acceleration
    float acceleration = 0.01f;  // adjust this as needed
    cameraPosition_ += direction * acceleration;

}

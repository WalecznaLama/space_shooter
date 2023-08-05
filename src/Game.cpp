#include "Game.h"

// TODO  black holes!/w gravity,
Game::Game()
        : window_("Space Shooter", sf::Vector2u(1280, 720)), // Initialize GameWindow with a title and size
          grid_(1280, 720),
          assets_(),
          player_(std::make_shared<Player>(sf::Vector2f(600, 300), assets_.playerTextures_))
{

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

    playerWidth_= 10, playerHeight_ = 30;
    enemyWidth_ = 200, enemyHeight_  = 200;

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
    gameOverText.setPosition(sf::Vector2f(window_.getSize().x / 2.0f, window_.getSize().y / 2.0f));

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

    sf::Vector2f linDisplacement = player_->getLinearVelocity() * deltaTime; // calculate how far the player should move
    sf::Vector2f newPosition = player_->getPosition() + linDisplacement; // calculate the player's new position
    float angDisplacement = player_->getAngularVelocity() * deltaTime;
    float newRotation = player_->getRotation() + angDisplacement;

    // check if the player's new bounding box collides with anything
    bool collidesWithSomething = false;

    // Check collision with enemies
    for (const auto& enemy : enemies_) {
        if (enemy.getBounds().intersects(player_->getBounds())) {
            collidesWithSomething = true;
            player_->setIsALive(false);
            break;
        }
    }

    // Check collision with enemy bullets
    if (!collidesWithSomething) {
        for (const auto& bullet : enemyBullets_) {
            if (bullet.getBounds().intersects(player_->getBounds())) {
                collidesWithSomething = true;
                player_->setIsALive(false);
                break;
            }
        }
    }

    // Check collision with powerups
    if (!collidesWithSomething) {
        for (auto& powerup : powerups_) {
            if (powerup.getBounds().intersects(player_->getBounds())) {
                powerup.setIsAlive(false);
                // TODO powerup stuff
                player_->multiplyLinearAcc(1.2);
                break;
            }
        }
    }

    // if the player's new position is inside the game area and doesn't collide with anything, move the player
    if (!collidesWithSomething && grid_.isInside(newPosition.x, newPosition.y)) {
        player_->setPosition(newPosition);
        player_->setRotation(newRotation);
    } else{
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
            if (bullet.getBounds().intersects(enemy.getBounds())) {
                collidesWithSomething = true;
                bullet.setIsAlive(false);
                enemy.setIsALive(false);
                enemy.setIsKilledByPlayer(true);
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
//    killCounterText_.setString("Score: " + std::to_string(kill_counter_));
    killCounterText_.setString("Score: " + std::to_string(playerBullets_.size()));
}

sf::Vector2f Game::randomSpawnPoint() {
    std::random_device rd;  // (seed)
    std::mt19937 gen(rd());  // generator liczb pseudolosowych
    std::uniform_int_distribution<> distr(0, 3);  // rozkład jednostajny

    int _spawnDirection = distr(gen);  // 0 - Up, 1 - Right, 2 - Down, 3 - Left
    float _x, _y;
    switch (_spawnDirection) {
        case Direction::Up:
            _x = (float)(std::rand() % window_.getSize().x);
            _y = 0;
            break;
        case Direction::Down:
            _x = (float)(std::rand() % window_.getSize().x);
            _y = window_.getSize().y - enemyHeight_;
            break;
        case Direction::Left:
            _x = 0;
            _y = (float)(std::rand() % window_.getSize().y);
            break;
        case Direction::Right:
            _x = window_.getSize().x - enemyWidth_;
            _y = (float)(std::rand() % window_.getSize().y);
            break;
    }
    return {_x, _y};
}

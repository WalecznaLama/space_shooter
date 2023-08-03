#include "Game.h"

Game::Game() {
    window_.create(sf::VideoMode(800, 600), "Space Shooter");

    // limit the framerate_ to 300 frames per second
    framerate_ = 150;
    window_.setFramerateLimit(framerate_);

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

    player_.init(window_.getSize(), assets_.playerEngineOffTexture);
    player_.addTexture("engine_on", assets_.playerEngineOnTexture);
    playerSpeed_ = sf::Vector2f(1.8f, 2.0f);
    enemySpeed_ = sf::Vector2f(0.8f, 0.1f);
    player_bullet_speed_ = 1.8f;
    enemy_bullet_speed_ = 1.2f;
    powerup_speed_ = 0.4f;
    shoot_time_player_ = 0.2f;
    shoot_time_enemy_ = 2.0f;

//    std::srand(std::time(nullptr));
}

void Game::run() {
    while (window_.isOpen()) {
        sf::Event event;
        while (window_.pollEvent(event))
            if (event.type == sf::Event::Closed)    window_.close();

        update();
        render();
    }
}

void Game::update() {
//    static sf::Clock enemySpawnClock;
//    sf::Time elapsed_enemy = enemySpawnClock.getElapsedTime();
//    if (elapsed_enemy.asSeconds() >= 3.0f) {  // every 3 seconds spawn enemy
//        enemies_.emplace_back(window_.getSize(), assets_.enemyTexture);
//        enemySpawnClock.restart();
//    }
//    static sf::Clock powerupSpawnClock;
//    sf::Time elapsed_powerup = powerupSpawnClock.getElapsedTime();
//    if (elapsed_powerup.asSeconds() >= 9.0f) {  // every 9 seconds spawn powerup
//        powerups_.emplace_back(window_.getSize(), assets_.powerupTexture);
//        powerupSpawnClock.restart();
//    }

    // update fps text
    static sf::Clock clock_fps;
    sf::Time elapsed_fps = clock_fps.getElapsedTime();
    float fps = 1.f / elapsed_fps.asSeconds();
    fpsText_.setString("FPS: " + std::to_string(static_cast<int>(fps)));
    clock_fps.restart();

    killCounterText_.setString("Score: " + std::to_string(kill_counter_));

    for (auto it = enemies_.rbegin(); it != enemies_.rend(); /* no increment here */) {
        it->setPlayerPosition(player_.getSprite().getPosition());
        it->update(enemySpeed_, playerBullets_);
        if (!it->isAlive()) {
            if (it->isKilledByPlayer()) kill_counter_++;
            // Convert reverse iterator to base (which will be one position forward in terms of direct iterator)
            auto directIt = it.base();
            // Move to the actual element in terms of direct iterator
            --directIt;
            // Erase the element and get the new iterator
            directIt = enemies_.erase(directIt);
            // Convert the direct iterator back to reverse iterator
            it = std::reverse_iterator<decltype(directIt)>(directIt);
        } else {
            ++it;
        }
    }

    enemiesShoot();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player_.canShoot(shoot_time_player_))
        playerBullets_.emplace_back(window_.getSize(),player_.getPosition(),
                                    assets_.playerBulletTexture,player_.getSprite().getRotation());

    bullets_update();
    powerups_update();

    player_.update(playerSpeed_, enemyBullets_);
    player_.checkEnemyCollision(enemies_);
    if (!player_.isAlive()) gameOver();
}

void Game::render() {
    window_.clear();
    window_.draw(backgroundSprite_);  // draw the background
    for (const Powerup& powerup : powerups_)     powerup.draw(window_);
    for (const Bullet& bullet : playerBullets_)  bullet.draw(window_);
    for (const Bullet& bullet : enemyBullets_)   bullet.draw(window_);
    for (const Enemy& enemy : enemies_)          enemy.draw(window_);
    player_.draw(window_);

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
        sf::Event event;
        while (window_.pollEvent(event))
            if (event.type == sf::Event::Closed)    window_.close();

        window_.clear();
        window_.draw(gameOverText);
        window_.display();
    }
}

void Game::enemiesShoot() {
    for (auto& enemy : enemies_)
        if (enemy.canShoot(shoot_time_enemy_))
            enemyBullets_.emplace_back(window_.getSize() ,enemy.getPosition(),
                                       assets_.enemyBulletTexture,enemy.getSprite().getRotation());
}

void Game::bullets_update() {
    for (int i = playerBullets_.size() - 1; i >= 0; --i) {
        Bullet& bullet = playerBullets_[i];
        bullet.update(-player_bullet_speed_);
        if (bullet.isOffScreen())   {
            playerBullets_.erase(playerBullets_.begin() + i);
        }
    }

    for (int i = enemyBullets_.size() - 1; i >= 0; --i) {
        Bullet& bullet = enemyBullets_[i];
        bullet.update(enemy_bullet_speed_);
        if (bullet.isOffScreen()) {
            enemyBullets_.erase(enemyBullets_.begin() + i); }
    }
}

void Game::powerups_update() {
    sf::FloatRect playerBounds = player_.getSprite().getGlobalBounds();

    for (int i = powerups_.size() - 1; i >= 0; --i) {
        Powerup& powerup = powerups_[i];
        powerup.update(powerup_speed_);
        sf::FloatRect powerupBounds = powerup.getSprite().getGlobalBounds();

        // remove off screen
        if(powerup.isOffScreen()) {
            powerups_.erase(powerups_.begin() + i);
        }

        if (playerBounds.intersects(powerupBounds)){
            powerups_.erase(powerups_.begin() + i);
            player_.multiplyEngineForce(1.3);
        }
    }
}



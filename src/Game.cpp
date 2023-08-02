#include "Game.h"

Game::Game() {
    window.create(sf::VideoMode(800, 600), "Space Shooter");

    // limit the framerate to 300 frames per second
    framerate = 150;
    window.setFramerateLimit(framerate);

    // set the texture to the sprite
    backgroundSprite.setTexture(assets.backgroundTexture);

    // set up fps and killCounter text
    fpsText.setFont(assets.font);
    fpsText.setCharacterSize(20);  // in pixels
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10, 10);  // top left corner

    killCounterText.setFont(assets.font);
    killCounterText.setCharacterSize(40);  // in pixels
    killCounterText.setFillColor(sf::Color::Red);
    killCounterText.setPosition(10, window.getSize().y - 50);  // bottom left corner

    player.init(window.getSize(), assets.playerTexture);
    player_speed = sf::Vector2f(1.8f, 0.0001f);
    enemy_speed = sf::Vector2f(0.8f, 0.1f);
    player_bullet_speed = 1.8f;
    enemy_bullet_speed = 1.2f;
    shoot_time_player = 0.2f;
    shoot_time_enemy = 2.0f;

//    std::srand(std::time(nullptr));
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)    window.close();

        update();
        render();

        if (!player.isALive()) gameOver();
    }
}

void Game::update() {
    static sf::Clock enemySpawnClock;
    sf::Time elapsed_enemy = enemySpawnClock.getElapsedTime();
    if (elapsed_enemy.asSeconds() >= 3.0f) {  // every 3 seconds spawn enemy
        enemies.emplace_back(window.getSize(), assets.enemyTexture);
        enemySpawnClock.restart();
    }
    static sf::Clock powerupSpawnClock;
    sf::Time elapsed_powerup = powerupSpawnClock.getElapsedTime();
    if (elapsed_powerup.asSeconds() >= 9.0f) {  // every 9 seconds spawn powerup
        powerups.emplace_back(window.getSize(), assets.powerupTexture);
        powerupSpawnClock.restart();
    }

    // update fps text
    static sf::Clock clock_fps;
    sf::Time elapsed_fps = clock_fps.getElapsedTime();
    float fps = 1.f / elapsed_fps.asSeconds();
    fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
    clock_fps.restart();

    killCounterText.setString("Score: " + std::to_string(kill_counter));

//    for (auto& enemy : enemies) {
//        enemy.update(enemy_speed.x, enemy_speed.y, player.getSprite().getPosition(), playerBullets);
//        if (!enemy.alive) {
//            // jak usunąć enemy z wektora paine komputerze w tym miejscu
//        }
//    }

    for (auto it = enemies.rbegin(); it != enemies.rend(); /* no increment here */) {
        it->update(enemy_speed.x, enemy_speed.y, player.getSprite().getPosition(), playerBullets);
        if (!it->isAlive()) {
            if (it->isKilledByPlayer()) kill_counter++;
            // Convert reverse iterator to base (which will be one position forward in terms of direct iterator)
            auto directIt = it.base();
            // Move to the actual element in terms of direct iterator
            --directIt;
            // Erase the element and get the new iterator
            directIt = enemies.erase(directIt);
            // Convert the direct iterator back to reverse iterator
            it = std::reverse_iterator<decltype(directIt)>(directIt);
        } else {
            ++it;
        }
    }

    enemiesShoot();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.canShoot(shoot_time_player))
        playerBullets.emplace_back(player.getPosition(), assets.playerBulletTexture,
                                   player.getSprite().getRotation());

    bullets_update();
    powerups_update();

    player.update(window.getSize(), player_speed, enemies, enemyBullets);
}

void Game::render() {
    window.clear();
    window.draw(backgroundSprite);  // draw the background
    for (const Powerup& powerup : powerups)     powerup.draw(window);
    for (const Bullet& bullet : playerBullets)  bullet.draw(window);
    for (const Bullet& bullet : enemyBullets)   bullet.draw(window);
    for (const Enemy& enemy : enemies)          enemy.draw(window);
    player.draw(window);

    window.draw(fpsText);  // draw the fps text
    window.draw(killCounterText);  // draw the killCounter text
    window.display();
}

void Game::gameOver() {
    sf::Text gameOverText;
    gameOverText.setFont(assets.font);
    gameOverText.setString("Game Over!\nFinal Score: " + std::to_string(kill_counter));
    gameOverText.setCharacterSize(24);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);

    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    gameOverText.setPosition(sf::Vector2f(window.getSize().x/2.0f,window.getSize().y/2.0f));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)    window.close();

        window.clear();
        window.draw(gameOverText);
        window.display();
    }
}

void Game::enemiesShoot() {
    for (auto& enemy : enemies) {
        if (enemy.canShoot(shoot_time_enemy)) {
            enemyBullets.emplace_back(enemy.getPosition(), assets.enemyBulletTexture,
                                      enemy.getSprite().getRotation());
        }
    }
}

void Game::bullets_update() {
    for (int i = playerBullets.size() - 1; i >= 0; --i) {
        Bullet& bullet = playerBullets[i];
        bullet.update(-player_bullet_speed);

        if (bullet.getPosition().y < 0) {
            playerBullets.erase(playerBullets.begin() + i);
        }
    }

    for (int i = enemyBullets.size() - 1; i >= 0; --i) {
        Bullet& bullet = enemyBullets[i];
        bullet.update(enemy_bullet_speed);

        if (bullet.getPosition().y > window.getSize().y) {
            enemyBullets.erase(enemyBullets.begin() + i);
        }
    }
}

void Game::powerups_update() {
    sf::FloatRect playerBounds = player.getSprite().getGlobalBounds();

    for (int i = powerups.size() - 1; i >=0; --i) {
        Powerup& powerup = powerups[i];
        powerup.update(0.4);
        sf::FloatRect powerupBounds = powerup.getSprite().getGlobalBounds();

        // remove off screen
        if(powerup.getPosition().y > window.getSize().y)    powerups.erase(powerups.begin() + i);

        if (playerBounds.intersects(powerupBounds)){
            powerups.erase(powerups.begin() + i);
//            player_speed
                //TODO powerups stuff
        }

    }
}


#include "Game.h"

Game::Game() {
    window.create(sf::VideoMode(800, 600), "Space Shooter");

    // limit the framerate to 300 frames per second
    framerate = 150;
    window.setFramerateLimit(framerate);

    // load textures
    backgroundTexture = assets.loadTexture("resources/space.png");
    playerTexture = assets.loadTexture("resources/player.png");
    enemyTexture = assets.loadTexture("resources/enemy.png");
    playerBulletTexture = assets.loadTexture("resources/player_bullet.png");
    enemyBulletTexture = assets.loadTexture("resources/enemy_bullet.png");
    powerupTexture = assets.loadTexture("resources/powerup1.png");

    // load font
    font = assets.loadFont("resources/Roboto-Medium.ttf");

    // set the texture to the sprite
    backgroundSprite.setTexture(backgroundTexture);

    // set up fps and killCounter text
    fpsText.setFont(font);
    fpsText.setCharacterSize(20);  // in pixels
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10, 10);  // top left corner

    killCounterText.setFont(font);
    killCounterText.setCharacterSize(40);  // in pixels
    killCounterText.setFillColor(sf::Color::Red);
    killCounterText.setPosition(10, window.getSize().y - 50);  // bottom left corner

    player.init(window.getSize(), playerTexture);
    player_speed = 1.8f;
    enemy_speed = 0.8f;
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

        if (is_game_over) gameOver();
    }
}

void Game::update() {
    static sf::Clock enemySpawnClock;
    sf::Time elapsed_enemy = enemySpawnClock.getElapsedTime();
    if (elapsed_enemy.asSeconds() >= 3.0f) {  // every 3 seconds spawn enemy
        enemies.emplace_back(window.getSize(), enemyTexture);
        enemySpawnClock.restart();
    }
    static sf::Clock powerupSpawnClock;
    sf::Time elapsed_powerup = powerupSpawnClock.getElapsedTime();
    if (elapsed_powerup.asSeconds() >= 5.0f) {  // every 5 seconds spawn powerup
        powerups.emplace_back(window.getSize(), powerupTexture);
        powerupSpawnClock.restart();
    }

    // update fps text
    static sf::Clock clock_fps;
    sf::Time elapsed_fps = clock_fps.getElapsedTime();
    float fps = 1.f / elapsed_fps.asSeconds();
    fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
    clock_fps.restart();

    killCounterText.setString("Score: " + std::to_string(kill_counter));

    updateEnemies();
    checkBulletEnemyCollisions();
    removeEnemiesOffScreen();
    enemiesShoot();


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.canShoot(shoot_time_player))
        playerBullets.emplace_back(player.getPosition(), playerBulletTexture);

    bullets_update();
    powerups_update();

    player.update(window.getSize(), player_speed);
    checkPlayerCollision();
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

void Game::checkPlayerCollision() {
    sf::FloatRect playerBounds = player.getSprite().getGlobalBounds();

    for (const auto& enemy : enemies) {
        sf::FloatRect enemyBounds = enemy.getSprite().getGlobalBounds();

        if (playerBounds.intersects(enemyBounds)) {
            // Player and enemy have collided
            is_game_over = true;
            return;
        }
    }

    for (const auto& bullet : enemyBullets) {
        sf::FloatRect bulletBounds = bullet.getSprite().getGlobalBounds();

        if (playerBounds.intersects(bulletBounds)) {
            // Player and bullet have collided
            is_game_over = true;
            return;
        }
    }
}

void Game::gameOver() {
    sf::Text gameOverText;
    gameOverText.setFont(font);
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

void Game::updateEnemies() {
    for (auto& enemy : enemies) {
        enemy.update(enemy_speed);
    }
}

void Game::checkBulletEnemyCollisions() {
    for (int i = enemies.size() - 1; i >= 0; --i) {
        for (int j = playerBullets.size() - 1; j >= 0; --j) {
            if (enemies[i].getSprite().getGlobalBounds().intersects(playerBullets[j].getSprite().getGlobalBounds())) {
                enemies.erase(enemies.begin() + i);
                playerBullets.erase(playerBullets.begin() + j);
                kill_counter++;
                break;
            }
        }
    }
}

void Game::removeEnemiesOffScreen() {
    for (int i = enemies.size() - 1; i >= 0; --i) {
        if (enemies[i].getPosition().y > window.getSize().y) {
            enemies.erase(enemies.begin() + i);
        }
    }
}

void Game::enemiesShoot() {
    for (auto& enemy : enemies) {
        if (enemy.canShoot(shoot_time_enemy)) {
            enemyBullets.emplace_back(enemy.getPosition(), enemyBulletTexture);
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
    for (int i = powerups.size() - 1; i >=0; --i) {
        Powerup& powerup = powerups[i];
        powerup.update(0.2, 0.2, 100);

        if(powerup.getPosition().y > window.getSize().y) {
            powerups.erase(powerups.begin() + i);
        }
    }
}


//
// Created by rav on 31.07.23.
//

#include "Game.h"

Game::Game() {
    window.create(sf::VideoMode(800, 600), "Space Shooter");

    // limit the framerate to 300 frames per second
    window.setFramerateLimit(300);

    // load background texture
    if (!backgroundTexture.loadFromFile("resources/space.png")) {
        std::cerr << "Failed to load background\n";
        std::exit(1);
    }
    // set the texture to the sprite
    backgroundSprite.setTexture(backgroundTexture);

    if (!playerTexture.loadFromFile("resources/player.png") ||
        !enemyTexture.loadFromFile("resources/enemy.png") ||
        !playerBulletTexture.loadFromFile("resources/player_bullet.png") ||
        !enemyBulletTexture.loadFromFile("resources/enemy_bullet.png")) {
        std::cerr << "Failed to load textures\n";
        std::exit(1);
    }

    // load font
    if (!font.loadFromFile("resources/Roboto-Medium.ttf")) {
        std::cerr << "Failed to load font\n";
    }

    // set up fps and killCounter text
    fpsText.setFont(font);
    fpsText.setCharacterSize(20);  // in pixels
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10, 10);  // top left corner

    killCounterText.setFont(font);
    killCounterText.setCharacterSize(40);  // in pixels
    killCounterText.setFillColor(sf::Color::Red);
    killCounterText.setPosition(10, window.getSize().y - 50);  // top right corner


    player.init(window.getSize(), playerTexture);
    player_bullet_speed = 0.9f;
    enemy_bullet_speed = 0.6f;
    kill_counter = 0;
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        update();
        render();
    }
}

void Game::update() {
    static sf::Clock clock;
    sf::Time elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= 3.0f) {  // every 2 second spawn enemy
        enemies.emplace_back(window.getSize(), enemyTexture);
        clock.restart();
    }

    // update fps text
    static sf::Clock clock_fps;
    sf::Time elapsed_fps = clock_fps.getElapsedTime();
    float fps = 1.f / elapsed_fps.asSeconds();
    fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
    clock_fps.restart();


    for (int i = enemies.size() - 1; i >= 0; --i) {
        Enemy& enemy = enemies[i];
        enemy.update();

        // check collision with player bullets
        for (int j = playerBullets.size() - 1; j >= 0; --j) {
            Bullet& bullet = playerBullets[j];

            if (enemy.getSprite().getGlobalBounds().intersects(bullet.getSprite().getGlobalBounds())) {
                // collision occurred, destroy the enemy and the bullet
                enemies.erase(enemies.begin() + i);
                playerBullets.erase(playerBullets.begin() + j);
                kill_counter++;
                break;  // enemy is destroyed, no need to check other bullets
            }
        }

        if (enemy.getPosition().y > window.getSize().y) {
            enemies.erase(enemies.begin() + i);
        }

        if (enemy.canShoot()) {
            enemyBullets.emplace_back(enemy.getPosition(), enemyBulletTexture);
        }
    }

    killCounterText.setString("Score: " + std::to_string(kill_counter));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.canShoot()) {
        playerBullets.emplace_back(player.getPosition(), playerBulletTexture);
    }

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

    player.update(window.getSize());
}

void Game::render() {
    window.clear();
    window.draw(backgroundSprite);  // draw the background
    for (const Enemy& enemy : enemies)  enemy.draw(window);
    for (const Bullet& bullet : playerBullets)  bullet.draw(window);
    for (const Bullet& bullet : enemyBullets)  bullet.draw(window);
    player.draw(window);

    window.draw(fpsText);  // draw the fps text
    window.draw(killCounterText);  // draw the killCounter text
    window.display();
}


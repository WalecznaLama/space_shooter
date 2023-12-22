#include "Game.h"

// TODO grid - more than one cell per object
Game::Game()
        : window_("Space Shooter", sf::Vector2u(1280, 720)), // Initialize GameWindow with a title and size
          grid_(900, 900),
          assets_(),
          projectileManager_(assets_, grid_),
          enemyManager_(assets_, projectileManager_, grid_),
          playerManager_(assets_, projectileManager_, grid_),
          powerupManager_(assets_, grid_),
          spaceObjectManager_(assets_, grid_)
{
    setGui();
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

    sf::Vector2f spaceObjectsNetForce = spaceObjectManager_.update(playerManager_.player_->getPos());
    projectileManager_.update(elapsed);
    playerManager_.update(spaceObjectsNetForce, elapsed);
    enemyManager_.update(playerManager_.player_->getPos(), elapsed);
    powerupManager_.update(playerManager_.player_->getPos(), elapsed);
    updateGui(elapsed);

    calculateCameraPos();
    window_.updateView(cameraPos_);
    if (!playerManager_.player_->getIsAlive()) gameOver();
    updateClock_.restart();
}

void Game::render() {
    window_.clear();
    window_.draw(backgroundSprite_);  // draw the background
    powerupManager_.render(window_.getRenderWindow());
    projectileManager_.render(window_.getRenderWindow());
    enemyManager_.render(window_.getRenderWindow());
    playerManager_.render(window_.getRenderWindow());
    spaceObjectManager_.render(window_.getRenderWindow());
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

void Game::updateGui(float deltaTime) {
    float fps = 1.f / deltaTime;
    fpsText_.setString("FPS: " + std::to_string(static_cast<int>(fps)));
    killCounterText_.setString("Score: " + std::to_string(killCounter_));
    debugText_.setString("X: " + std::to_string(playerManager_.player_->getPos().x) + '\n' +
                         "Y: " + std::to_string(playerManager_.player_->getPos().y));

//    debugText_.setString("X: " + std::to_string( powerups_[0].getAngAcc()));

    float hp_percent = playerManager_.player_->getHp() * 1. / playerManager_.player_->getMaxHp();
    heartSprite_.setTextureRect(sf::IntRect(0, 0,
                                            heartSprite_.getTexture()->getSize().x * hp_percent,
                                            heartSprite_.getTexture()->getSize().y));
}

void Game::calculateCameraPos() {
    sf::Vector2f direction = playerManager_.player_->getPos() - cameraPos_;
    // move the camera towards the player with a certain acceleration
    cameraPos_ += direction * cameraAcc_;
}

void Game::setGui() {
    cameraPos_ = playerManager_.player_->getPos();

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

#include "AssetManager.h"

AssetManager::AssetManager() {
    init();
}


sf::Texture &AssetManager::loadTexture(const std::string &filename) {
    // Use the filename as the key
    auto& texture = textures_[filename];

    // Only load the texture if it's not already loaded
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Failed to load textures_\n";
        std::exit(1);
    }

    return texture;
}

sf::Font &AssetManager::loadFont(const std::string &filename) {
    auto& _font = fonts_[filename];
    if (!_font.loadFromFile(filename)) {
        std::cerr << "Failed to load font\n";
        std::exit(1);
    }
    return _font;
}

void AssetManager::init() {
    // load textures_
    playerTextures_["main"] = loadTexture("resources/player_engine_off.png");
    playerTextures_["engine_on"] = loadTexture("resources/player_engine_on.png");
    playerTextures_["boost"] = loadTexture("resources/player_boost.png");

    enemyTexture = loadTexture("resources/enemy.png");

    playerBulletTexture = loadTexture("resources/player_bullet.png");
    enemyBulletTexture = loadTexture("resources/enemy_bullet.png");

    powerupTexture = loadTexture("resources/powerup1.png");

    backgroundTexture = loadTexture("resources/space.png");
    // load font
    font = loadFont("resources/Roboto-Medium.ttf");
}

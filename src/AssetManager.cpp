#include "AssetManager.h"

AssetManager::AssetManager() = default;


sf::Texture &AssetManager::loadTexture(const std::string &filename) {
    // Use the filename as the key
    auto& texture = textures[filename];

    // Only load the texture if it's not already loaded
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Failed to load textures\n";
        std::exit(1);
    }

    return texture;
}

sf::Font &AssetManager::loadFont(const std::string &filename) {
    auto& font = fonts[filename];
    if (!font.loadFromFile(filename)) {
        std::cerr << "Failed to load font\n";
        std::exit(1);
    }
    return font;
}

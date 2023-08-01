#ifndef SPACE_SHOOTER_ASSETMANAGER_H
#define SPACE_SHOOTER_ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class AssetManager {
public:
    AssetManager();
    sf::Texture& loadTexture(const std::string& filename);
    sf::Font& loadFont(const std::string& filename);

private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
};


#endif //SPACE_SHOOTER_ASSETMANAGER_H

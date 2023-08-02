#ifndef SPACE_SHOOTER_ASSETMANAGER_H
#define SPACE_SHOOTER_ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class AssetManager {
public:
    AssetManager();
    void init();
    sf::Texture& loadTexture(const std::string& filename);
    sf::Font& loadFont(const std::string& filename);

    sf::Texture backgroundTexture;
    sf::Texture playerTexture;
    sf::Texture enemyTexture;
    sf::Texture playerBulletTexture;
    sf::Texture enemyBulletTexture;
    sf::Texture powerupTexture;

    sf::Font font;

private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
};


#endif //SPACE_SHOOTER_ASSETMANAGER_H

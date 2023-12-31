#ifndef SPACE_SHOOTER_ASSETMANAGER_H
#define SPACE_SHOOTER_ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class AssetManager {
public:
    AssetManager();
    const sf::Texture& getTexture(const std::string& name) const;
    sf::Texture& loadTexture(const std::string& filename);
    sf::Font& loadFont(const std::string& filename);
    sf::Texture backgroundTexture;
    sf::Texture enemyTexture;
    sf::Texture playerBulletTexture;
    sf::Texture enemyBulletTexture;
    sf::Texture powerupTexture;
    sf::Texture heartTexture;
    sf::Texture planetTexture;
    std::map<std::string, sf::Texture> playerTextures_;

    sf::Font font;

private:
    std::map<std::string, sf::Texture> textures_;
    std::map<std::string, sf::Font> fonts_;
};


#endif //SPACE_SHOOTER_ASSETMANAGER_H

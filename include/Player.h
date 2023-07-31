#ifndef SPACE_SHOOTER_PLAYER_H
#define SPACE_SHOOTER_PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    void init(const sf::Vector2u& windowSize, const sf::Texture& texture);
    void draw(sf::RenderWindow& window) const;
    void update(const sf::Vector2u& windowSize);
    sf::Vector2f getPosition();
    bool canShoot();

private:
    sf::Sprite sprite;
    sf::Clock shootClock;
    sf::Vector2u texture_size;
};

#endif //SPACE_SHOOTER_PLAYER_H

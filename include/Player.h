#ifndef SPACE_SHOOTER_PLAYER_H
#define SPACE_SHOOTER_PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    void init(const sf::Vector2u& windowSize);
    void draw(sf::RenderWindow& window) const;
    void update(const sf::Vector2u& windowSize);

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif //SPACE_SHOOTER_PLAYER_H

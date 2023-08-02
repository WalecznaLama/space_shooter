#ifndef SPACE_SHOOTER_PLAYER_H
#define SPACE_SHOOTER_PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    void init(const sf::Vector2u& windowSize, const sf::Texture& texture);
    void draw(sf::RenderWindow& window) const;
    void update(const sf::Vector2u& windowSize, float speed);
    sf::Vector2f getPosition();
    bool canShoot(float time_to_shoot);
    const sf::Sprite& getSprite() const;

private:
    sf::Sprite sprite;
    sf::Clock shootClock;
};

#endif //SPACE_SHOOTER_PLAYER_H

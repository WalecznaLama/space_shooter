#ifndef SPACE_SHOOTER_ENEMY_H
#define SPACE_SHOOTER_ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(const sf::Vector2u& windowSize,  const sf::Texture& texture);
    void draw(sf::RenderWindow& window) const;
    void update();
    sf::Vector2f getPosition();
    bool canShoot();
    const sf::Sprite& getSprite() const;

private:
    sf::Sprite sprite;
    sf::Clock shootClock;
};

#endif //SPACE_SHOOTER_ENEMY_H

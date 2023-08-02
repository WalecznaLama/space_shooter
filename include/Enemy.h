#ifndef SPACE_SHOOTER_ENEMY_H
#define SPACE_SHOOTER_ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(const sf::Vector2u& windowSize,  const sf::Texture& texture);
    void draw(sf::RenderWindow& window) const;
    void update(float speed);
    sf::Vector2f getPosition();
    bool canShoot(float time_to_shoot);
    const sf::Sprite& getSprite() const;

private:
    sf::Sprite sprite;
    sf::Clock shootClock;
    bool first_shot_fired = false;
};

#endif //SPACE_SHOOTER_ENEMY_H

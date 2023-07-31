#ifndef SPACE_SHOOTER_BULLET_H
#define SPACE_SHOOTER_BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(const sf::Vector2f& position, const sf::Texture& texture);
    void draw(sf::RenderWindow& window) const;
    void update(float dy);
    sf::Vector2u texture_size;
    sf::Vector2f getPosition();
    const sf::Sprite& getSprite() const;

private:
    sf::Sprite sprite;
};


#endif //SPACE_SHOOTER_BULLET_H

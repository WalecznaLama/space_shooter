#ifndef SPACE_SHOOTER_ENEMY_H
#define SPACE_SHOOTER_ENEMY_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Enemy  : public Entity {
public:
    Enemy(const sf::Vector2u& windowSize,  const sf::Texture& texture);
    void init(const sf::Vector2u& windowSize, const sf::Texture& texture) override;
    void draw(sf::RenderWindow& window) const override;
    void update(const sf::Vector2f& speed, std::vector <Bullet> &bullets) override;
    bool isKilledByPlayer();
    void setPlayerPosition(const sf::Vector2f& playerPosition);

private:
    sf::Vector2f playerPosition_;
    float max_tilt_;
};

#endif //SPACE_SHOOTER_ENEMY_H

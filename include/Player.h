#ifndef SPACE_SHOOTER_PLAYER_H
#define SPACE_SHOOTER_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Bullet.h"

class Player {
public:
    Player();
    void init(const sf::Vector2u& windowSize, const sf::Texture& texture);
    void draw(sf::RenderWindow& window) const;
    void update(const sf::Vector2u& windowSize,const sf::Vector2f& speed,
                const std::vector<Enemy>& enemies, const std::vector<Bullet>& enemyBullets);
    sf::Vector2f getPosition();
    bool canShoot(float time_to_shoot);
    const sf::Sprite& getSprite() const;
    void checkPlayerCollision(const std::vector<Enemy>& enemies, const std::vector<Bullet>& enemyBullets);

    bool player_alive = true;
private:
    sf::Sprite sprite;
    sf::Clock shootClock;
};

#endif //SPACE_SHOOTER_PLAYER_H

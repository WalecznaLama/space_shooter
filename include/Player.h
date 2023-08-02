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
    void userMovement(const sf::Vector2f& speed, sf::Time elapsed);
    bool isALive();

private:
    sf::Sprite sprite;
    sf::Clock shootClock;
    sf::Clock updateClock;
    float current_dx = 0;
    bool alive = true;
};

#endif //SPACE_SHOOTER_PLAYER_H

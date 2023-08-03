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

    void setRotationAcceleration(float rotationAcceleration);
    void multiplyRotationAcceleration(float k);
    float getRotationAcceleration() const;

private:
    sf::Sprite sprite;
    sf::Clock shootClock;
    sf::Clock updateClock;
    sf::Vector2f current_speed;
    float acceleration;
    bool alive = true;
};

#endif //SPACE_SHOOTER_PLAYER_H

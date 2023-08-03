#ifndef SPACE_SHOOTER_ENTITY_H
#define SPACE_SHOOTER_ENTITY_H

#include <SFML/Graphics.hpp>
#include "Bullet.h"

class Entity {

public:
    virtual void init(const sf::Vector2u& windowSize, const sf::Texture& texture) = 0;
    virtual void draw(sf::RenderWindow& window) const;
    virtual void update(const sf::Vector2f& speed, std::vector<Bullet>& bullets) = 0;
    virtual sf::Vector2f getPosition();
    virtual bool canShoot(float time_to_shoot);
    virtual const sf::Sprite& getSprite() const;
    virtual void checkBulletsCollision(std::vector<Bullet>& bullets);
    virtual bool isAlive();
    virtual void addTexture(const std::string&, const sf::Texture& texture);

protected:
    std::map<std::string, sf::Texture> textures_;
    sf::Sprite sprite_;
    sf::Clock shootClock_;
    sf::Clock updateClock_;
    sf::Vector2u windowSize_;
    bool alive_ = true;
    bool first_shot_fired_ = false;
    bool killed_by_bullet_ = false;

};

#endif //SPACE_SHOOTER_ENTITY_H

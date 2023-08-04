#ifndef SPACE_SHOOTER_ENTITY_H
#define SPACE_SHOOTER_ENTITY_H

#include <SFML/Graphics.hpp>
#include "Bullet.h"

class Entity {

public:
    virtual void init(const sf::Vector2u& windowSize, const sf::Texture& texture) = 0;
    virtual void update(const sf::Vector2f& speed, std::vector<Bullet>& bullets) = 0;
    virtual void draw(sf::RenderWindow& window) const;
    virtual sf::Vector2f getPosition() const;
    virtual float getRotation() const;
    virtual bool canShoot(float time_to_shoot);
    virtual const sf::Sprite& getSprite() const;
    virtual void checkBulletsCollision(std::vector<Bullet>& bullets);
    virtual bool isAlive();
    virtual void addTexture(const std::string&, const sf::Texture& texture);

protected:
    virtual sf::Vector2f normalize(const sf::Vector2f& vector);
    virtual float length(const sf::Vector2f& vec);
    std::map<std::string, sf::Texture> textures_;
    sf::Sprite sprite_;
    sf::Clock shootClock_;
    sf::Clock updateClock_;
    sf::Vector2u windowSize_;
    bool alive_ = true;
    bool first_shot_fired_ = false;
    bool killed_by_bullet_ = false;

    sf::Vector2f velocity_ = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f position_;
    float rotation_ = 0.0;
    float acceleration_ = 0.0;
};

#endif //SPACE_SHOOTER_ENTITY_H

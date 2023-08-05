#ifndef SPACE_SHOOTER_ENTITY_H
#define SPACE_SHOOTER_ENTITY_H

#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <map>
#include <random>

class Entity {

public:
    virtual void draw(sf::RenderWindow& window) const;
    virtual sf::Vector2f getPosition() const;
    virtual void setPosition(sf::Vector2f& newPosition);
    virtual void setRotation(float newRotation);
    virtual void setVelocity(sf::Vector2f& newVelocity);
    virtual void setIsALive(bool isAlive);
    virtual float getRotation() const;
    virtual sf::Vector2f getLinearVelocity() const;
    virtual float getAngularVelocity() const;
    sf::FloatRect getBounds() const;
    virtual bool canShoot(float time_to_shoot);
    virtual const sf::Sprite& getSprite() const;
    virtual bool getIsAlive() const;
    virtual void addSprite(const std::string&, const sf::Texture& texture);

    template<typename T>
    int sgn(T val) { return (T(0) < val) - (val < T(0)); }

protected:
    static sf::Vector2f vectorNormalize(const sf::Vector2f& vector);
    static float vectorLength(const sf::Vector2f& vec);
    sf::Vector2f calculateForceDirection() const;
    sf::Vector2f calculateAcceleration(sf::Vector2f _engineForceDirection, float _x_acc, float deltaTime) const;
    std::map<std::string, sf::Sprite> sprites_;
    sf::Sprite mainSprite_;
    sf::Clock shootClock_;
    sf::Clock updateClock_;
    bool alive_ = true;
    bool firstShotFired_ = false;
    bool killedByBullet_ = false;

    sf::Vector2f velocity_ = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f position_;
    float rotation_ = 0.0;

    float maxAngularVel_; // deg / s
    float maxLinearVel_; // pixels / s
    float angularVel_ = 0; // deg / s
    float linAcc_; // pixels / s^s
    float angAcc_; // deg / s^2
};

#endif //SPACE_SHOOTER_ENTITY_H

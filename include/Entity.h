#ifndef SPACE_SHOOTER_ENTITY_H
#define SPACE_SHOOTER_ENTITY_H

#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <map>
#include <random>

class Entity {

public:
    virtual void draw(sf::RenderWindow& window) const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    void setPosition(sf::Vector2f& newPosition);
    void setRotation(float newRotation);
    void setVelocity(sf::Vector2f& newVelocity);
    float getRotation() const;
    float getRadius() const;
    float getMass() const;
    sf::Vector2f getLinearVelocity() const;
    float getAngularVelocity() const;
    sf::FloatRect getBounds() const;
    int getHp() const;
    float getMaxHp() const;
    bool canShoot(float time_to_shoot);
    const sf::Sprite& getSprite() const;
    void setIsAlive(bool isAlive);
    void setDamage(int damage);
    bool getIsAlive() const;
    void addSprite(const std::string&, const sf::Texture& texture);

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
    int hp_;
    int maxHp_;
    float mass_;

    sf::Vector2f velocity_ = sf::Vector2f(0.0f, 0.0f);
    sf::Vector2f position_;
    float rotation_ = 0.0;
    float collisionRadius_; // pixels
    float maxAngularVel_; // deg / s
    float maxLinearVel_; // pixels / s
    float angularVel_ = 0; // deg / s
    float linAcc_; // pixels / s^s
    float angAcc_; // deg / s^2
};

#endif //SPACE_SHOOTER_ENTITY_H

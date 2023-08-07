#ifndef SPACE_SHOOTER_OBJECT_H
#define SPACE_SHOOTER_OBJECT_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Object {
public:
    void setPosition(const sf::Vector2f& newPosition);
    sf::Vector2f getPosition() const;

    void setRotation(float newRotation);
    float getRotation() const;

    void setLinearVelocity(const sf::Vector2f& newVelocity);
    sf::Vector2f getLinearVelocity() const;

    void setLinearAcceleration(float newAcc);
    float getLinearAcceleration() const;

    void setAngularVelocity(float newVelocity);
    float getAngularVelocity() const;

    void setRadius(float newRadius);
    float getRadius() const;

    void setIsAlive(bool isAlive);
    bool getIsAlive() const;

    float getMass() const;

    sf::FloatRect getBounds() const;

    void addSprite(const std::string&, const sf::Texture& texture);
    const sf::Sprite& getSprite() const;

protected:
    void calculateLinearVelocity(float deltaTime);
    void calculateAngularVelocity(float deltaTime);
    static sf::Vector2f vectorNormalize(const sf::Vector2f& vector);
    static float vectorLength(const sf::Vector2f& vec);
    sf::Vector2f calculateForceDirection() const;
    sf::Vector2f calculateAcceleration(sf::Vector2f accelerationDirection, float deltaTime) const;
    static void scaleSprite( sf::Sprite& sprite, const sf::Vector2f &factor);
    static void scaleSprite( sf::Sprite& sprite, float factorX, float factorY);
    void spriteInit(const std::map<std::string, sf::Texture> &textures);
    void spriteInit(const sf::Texture& texture);
    void updateMainSpritePosition();
    std::map<std::string, sf::Sprite> sprites_;
    sf::Sprite mainSprite_;

    sf::Vector2f linVel_; // pixels / s
    float linAcc_; // pixels / s^s
    float maxLinVel_; // pixels / s
    float maxLinAcc_; // pixels / s^s

    float angVel_; // deg / s
    float angAcc_; // deg / s^2
    float maxAngVel_; // deg / s
    float maxAngAcc_; // deg / s^s

    sf::Vector2f position_; // pixels
    float rotation_; // deg

    float mass_;
    float radius_; // pixels

    bool alive_ = true;

    /// returns -> -1, 0, 1
    template<typename T>
    int getSign(T val) { return (T(0) < val) - (val < T(0)); }
};


#endif //SPACE_SHOOTER_OBJECT_H

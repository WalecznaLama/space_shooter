#ifndef SPACE_SHOOTER_SPACEOBJECT_H
#define SPACE_SHOOTER_SPACEOBJECT_H

#include <cmath>
#include <SFML/Graphics.hpp>

class SpaceObject {
public:
    static const float G_;
    SpaceObject(const sf::Texture &texture, const sf::Vector2f& initPosition,
                const sf::Vector2f& initVelocity, float initRotation,
                float radius, float density);

    void setVelocity(const sf::Vector2f &velocity);
    sf::Vector2f getVelocity() const;

    void setPosition(const sf::Vector2f &position);
    sf::Vector2f getPosition() const;

    void setRotation(float rotation);
    float getRotation() const;

    void setCollisionRadius(float collisionRadius);
    float getCollisionRadius() const;

    float getMass() const;
    const sf::Sprite& getSprite() const;
    sf::FloatRect getLocalBounds() const;
    void scaleSprite(const sf::Vector2f &factor);
    void scaleSprite(float factorX, float factorY);
    void setOriginSprite(float x, float y);

    void update();

private:
    sf::Vector2f velocity_;
    sf::Vector2f position_;
    float rotation_; // degrees
    float collisionRadius_; // pixels
    float density_;
    float mass_;

    sf::Sprite mainSprite_;

    float calculateMass(float radius);
};

#endif //SPACE_SHOOTER_SPACEOBJECT_H

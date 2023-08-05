#ifndef SPACE_SHOOTER_PASSIVEOBJECT_H
#define SPACE_SHOOTER_PASSIVEOBJECT_H

#include <SFML/Graphics.hpp>

class PassiveObject {
public:
    virtual void draw(sf::RenderWindow& window) const;
    virtual void update(const float &velocity) = 0;
    virtual sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    virtual void setIsAlive(bool alive);
    virtual bool getIsAlive() const;
    virtual float getRadius() const;

protected:
    sf::Sprite sprite_;
    sf::Vector2u windowSize_;
    bool alive_=true;
    float collisionRadius_=0; // pixels
};

#endif //SPACE_SHOOTER_PASSIVEOBJECT_H

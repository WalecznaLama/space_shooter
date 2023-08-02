#ifndef SPACE_SHOOTER_PASSIVEOBJECT_H
#define SPACE_SHOOTER_PASSIVEOBJECT_H

#include <SFML/Graphics.hpp>

class PassiveObject {
public:
    virtual void draw(sf::RenderWindow& window) const;
    virtual void update(const float &speed) = 0;
    virtual sf::Vector2f getPosition();
    virtual const sf::Sprite& getSprite() const;

protected:
    sf::Sprite sprite;
};

#endif //SPACE_SHOOTER_PASSIVEOBJECT_H

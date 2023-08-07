#ifndef SPACE_SHOOTER_PASSIVEOBJECT_H
#define SPACE_SHOOTER_PASSIVEOBJECT_H

#include "Object.h"

class PassiveObject : public Object{
public:
    virtual void draw(sf::RenderWindow& window) const;
    virtual void update(float deltaTime) = 0;

};

#endif //SPACE_SHOOTER_PASSIVEOBJECT_H

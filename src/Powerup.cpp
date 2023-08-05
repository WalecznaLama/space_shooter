#include "Powerup.h"
#include <cmath>
Powerup::Powerup(const sf::Vector2u& windowSize,const sf::Texture& texture) {
    sprite_.setTexture(texture);
    windowSize_ = windowSize;

    goingRight_ = true;

    std::srand(std::time(nullptr));
    uint bound_offset = windowSize_.x / 5;
    auto x = (float)(std::rand() % (windowSize.x - bound_offset*2));
    x += bound_offset;

    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
    sprite_.setPosition(x,  1);

    dyRange_ = 100;
}

void Powerup::update(const float& velocity) {
    if(fabs(dyFromSpawn_) > dyRange_) goingRight_ = !goingRight_;

    int direction;
    if(goingRight_) direction = 1;
    else direction = -1;
    float dx_dy = 30. * (M_PI / 180.);

    float dx = velocity * sinf(dx_dy);
    float dy = velocity * cosf(dx_dy);
    dyFromSpawn_ += direction * dx;
    sprite_.move(direction * dx, dy);
}

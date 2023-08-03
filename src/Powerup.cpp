#include "Powerup.h"
#include <cmath>
Powerup::Powerup(const sf::Vector2u& windowSize,const sf::Texture& texture) {
    sprite_.setTexture(texture);

    d_from_spawn_ = 0;
    going_right_ = true;

    std::srand(std::time(nullptr));
    auto x = (float)(std::rand() % windowSize.x);

    sprite_.setPosition(x, 0);
    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);

    d_range_ = 100;
}

void Powerup::update(const float& speed) {
    if(fabs(d_from_spawn_) > d_range_) going_right_ = !going_right_;

    int direction;
    if(going_right_) direction = 1;
    else direction = -1;
    float dx_dy = 30. * (M_PI / 180.);

    float dx = speed * sinf(dx_dy);
    float dy = speed * cosf(dx_dy);
    d_from_spawn_ += direction * dx;
    sprite_.move(direction * dx, dy);
}

#include "Powerup.h"
#include <cmath>
Powerup::Powerup(const sf::Vector2u& windowSize,const sf::Texture& texture) {
    sprite.setTexture(texture);

    d_from_spawn = 0;
    going_right = true;

    std::srand(std::time(nullptr));
    auto x = (float)(std::rand() % windowSize.x);

    sprite.setPosition(x, 0);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

    d_range = 100;
}

void Powerup::update(const float& speed) {
    if(fabs(d_from_spawn) > d_range)    going_right = !going_right;

    int direction;
    if(going_right) direction = 1;
    else direction = -1;
    float dx_dy = 30. * (M_PI / 180.);

    float dx = speed * sinf(dx_dy);
    float dy = speed * cosf(dx_dy);
    d_from_spawn += direction*dx;
    sprite.move(direction*dx, dy);
}

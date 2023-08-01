#include "Powerup.h"
#include <cmath>
Powerup::Powerup(const sf::Vector2u& windowSize,const sf::Texture& texture) {
    sprite.setTexture(texture);

    d_from_spawn = 0;
    going_right = true;

    std::srand(std::time(nullptr));
    auto x = (float)(std::rand() % windowSize.x);

    // Skalowanie do nowego rozmiaru
    float targetWidth = 40.0f;
    float targetHeight = 40.0f;
    // Obliczenie współczynnika skalowania
    float scaleX = targetWidth / texture.getSize().x;
    float scaleY = targetHeight / texture.getSize().y;
    // Zastosowanie skalowania
    sprite.setScale(scaleX, scaleY);

    sprite.setPosition(x, 0);
}

void Powerup::update(float dx, float dy, float d_range) {


    if(fabs(d_from_spawn) > d_range)    going_right = !going_right;

    int direction;

    if(going_right) direction = 1;
    else direction = -1;

    float directed_dx = direction*dx;
    d_from_spawn += directed_dx;

    sprite.move(directed_dx, dy);
}

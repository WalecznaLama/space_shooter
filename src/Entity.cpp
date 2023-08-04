#include "Entity.h"

bool Entity::canShoot(float time_to_shoot){
    sf::Time elapsed = shootClock_.getElapsedTime();
    float interval;

    if (!firstShotFired_) {
        interval = time_to_shoot / 10.f;
    } else {
        interval = time_to_shoot;
    }

    if (elapsed.asSeconds() >= interval) {
        shootClock_.restart();
        firstShotFired_ = true;
        return true;
    }
    return false;
}

void Entity::checkBulletsCollision(std::vector <Bullet> &bullets) {
    sf::FloatRect bounds = mainSprite_.getGlobalBounds();

    for (auto it = bullets.begin(); it != bullets.end(); ) {
        sf::FloatRect bulletBounds = it->getSprite().getGlobalBounds();

        if (bounds.intersects(bulletBounds)) {
            // Player and bullet have collided
            alive_ = false;
            killedByBullet_ = true;
            // Remove the bullet from the vector
            it = bullets.erase(it);
            // No need to increment the iterator in this case
        } else {
            ++it; // Only increment the iterator if no erasure happened
        }
    }
}

//void Entity::addTexture(const std::string& texture_name, const sf::Texture& texture) {
//    textures_[texture_name] = texture;
//}

void Entity::addSprite(const std::string& sprite_name, const sf::Texture& texture) {
    sprites_[sprite_name] = sf::Sprite(texture);
    sprites_[sprite_name].setOrigin(sprites_[sprite_name].getLocalBounds().width / 2,
                                    sprites_[sprite_name].getLocalBounds().height / 2);
}

float Entity::length(const sf::Vector2f& vec) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f Entity::normalize(const sf::Vector2f& vec) {
    float len = length(vec);
    if (len != 0) {
        return sf::Vector2f(vec.x / len, vec.y / len);
    } else {
        return sf::Vector2f(0, 0);
    }
}

void Entity::draw(sf::RenderWindow& window) const{ window.draw(mainSprite_); }

sf::Vector2f Entity::getPosition() const{ return mainSprite_.getPosition(); }

float Entity::getRotation() const { return rotation_; }

const sf::Sprite& Entity::getSprite() const{ return mainSprite_; }

bool Entity::isAlive() { return alive_; }


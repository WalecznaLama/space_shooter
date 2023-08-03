#include "Entity.h"

void Entity::draw(sf::RenderWindow& window) const{
    window.draw(sprite_);
}

sf::Vector2f Entity::getPosition(){
    return sprite_.getPosition();
}

bool Entity::canShoot(float time_to_shoot){
    sf::Time elapsed = shootClock_.getElapsedTime();
    float interval;

    if (!first_shot_fired_) {
        interval = time_to_shoot / 10.f;
    } else {
        interval = time_to_shoot;
    }

    if (elapsed.asSeconds() >= interval) {
        shootClock_.restart();
        first_shot_fired_ = true;
        return true;
    }
    return false;
}

const sf::Sprite& Entity::getSprite() const{
    return sprite_;
}

void Entity::checkBulletsCollision(std::vector <Bullet> &bullets) {
    sf::FloatRect bounds = sprite_.getGlobalBounds();

    for (auto it = bullets.begin(); it != bullets.end(); ) {
        sf::FloatRect bulletBounds = it->getSprite().getGlobalBounds();

        if (bounds.intersects(bulletBounds)) {
            // Player and bullet have collided
            alive_ = false;
            killed_by_bullet_ = true;
            // Remove the bullet from the vector
            it = bullets.erase(it);
            // No need to increment the iterator in this case
        } else {
            ++it; // Only increment the iterator if no erasure happened
        }
    }
}


bool Entity::isAlive() {
    return alive_;
}

void Entity::addTexture(const std::string& texture_name, const sf::Texture& texture) {
    textures_[texture_name] = texture;
}

#ifndef SPACE_SHOOTER_PLAYER_H
#define SPACE_SHOOTER_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Player : public Entity {
public:
    Player();
    void init(const sf::Vector2u& windowSize, const sf::Texture& texture) override;
    void update(const sf::Vector2f& speed, std::vector<Bullet>& bullets) override;
    void userMovement(const sf::Vector2f& speed, sf::Time elapsed);
    void checkEnemyCollision(const std::vector<Enemy>& enemies);

    void setRotationAcceleration(float rotationAcceleration);
    void multiplyRotationAcceleration(float k);
    float getRotationAcceleration() const;

private:
    sf::Vector2f currentSpeed_;
    bool user_input = false;
};

#endif //SPACE_SHOOTER_PLAYER_H

#ifndef SPACE_SHOOTER_PLAYER_H
#define SPACE_SHOOTER_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <cmath>

class Player : public Entity {
public:
    Player();
    void init(const sf::Vector2u& windowSize, const sf::Texture& texture) override;
    void update(const sf::Vector2f& speed, std::vector<Bullet>& bullets) override;
    void userMovement(const sf::Time& deltaTime);
    void checkEnemyCollision(const std::vector<Enemy>& enemies);

    void setEngineForce(float engineForce);
    float getEngineForce() const;
    void multiplyEngineForce(float k);

    float getRotation() const { return rotation_; }

private:
    bool user_input = false;
    float engineForce_;
    float angularAcc_; // deg / s^2
    float linearDecConst_; // deceleration = linearDecConst_ * (engineForce_ / mass_)
    float maxAngularVel_; // deg / s
    float maxLinearVel_; // pixels / s
    float angularVel_; // deg / s
};

#endif //SPACE_SHOOTER_PLAYER_H

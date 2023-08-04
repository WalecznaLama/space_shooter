#ifndef SPACE_SHOOTER_PLAYER_H
#define SPACE_SHOOTER_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <cmath>
#include <memory>

class Player : public Entity {
public:
    Player();
    void init(const sf::Vector2u& windowSize, const sf::Texture& texture) override;
    void update(const sf::Vector2f& speed, std::vector<Bullet>& bullets) override;
    void userMovement(const sf::Time& deltaTime);
    void checkEnemyCollision(const std::vector<Enemy>& enemies);

    void  setlinearAcc(float engineForce);
    float getlinearAcc() const;
    void multiplyEngineForce(float k);

    void calculateVelocity(const float& x_acc, const float& y_acc, const bool& brake, const float& deltaTime);

private:
    bool user_input_ = false;
    float linearAcc_; // pixels / s^s
    float angularAcc_; // deg / s^2
    float breakDecc_; // pixels / s^s
    float constDecc_; // pixels / s^s
    float engineDeccDivider_; // if (backward) acceleration /= engineDeccDivider_;
    float maxAngularVel_; // deg / s
    float maxLinearVel_; // pixels / s
    float angularVel_; // deg / s
};

#endif //SPACE_SHOOTER_PLAYER_H

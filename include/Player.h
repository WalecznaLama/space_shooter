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

    float getlinearAcc() const;
    void setLinearAcc(float linearAcc);
    void multiplyLinearAcc(float k);

    template <typename T>
    int sgn(T val);

private:
    float linAcc_; // pixels / s^s
    float angAcc_; // deg / s^2
    float angBreakDecc_; // deg / s^2
    float angConstDecc_; // deg / s^2
    float linBreakDecc_; // pixels / s^2
    float linConstDecc_; // pixels / s^2

    float decelerationDivider_; // if (backward) acceleration /= decelerationDivider_;
    float maxAngularVel_; // deg / s
    float maxLinearVel_; // pixels / s
    float angularVel_; // deg / s

    bool user_input_ = false;
    bool boost_active_ = false;

    void calculateVelocity(const float& lin_acc, const float& theta_acc, const bool& brake, const float& deltaTime);
    void calculateAngularVelocity(float theta_acc, float deltaTime);
    sf::Vector2f calculateForceDirection();
    sf::Vector2f calculateAcceleration(sf::Vector2f _engineForceDirection, float _x_acc, float deltaTime);
    sf::Vector2f calculateDeceleration(float deltaTime);
    sf::Vector2f calculateBrakeDeceleration(float deltaTime);

};

#endif //SPACE_SHOOTER_PLAYER_H

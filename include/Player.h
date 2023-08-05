#ifndef SPACE_SHOOTER_PLAYER_H
#define SPACE_SHOOTER_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <cmath>
#include <memory>

class Player : public Entity {
public:
    Player(sf::Vector2f spawn_point, const std::map<std::string, sf::Texture> &textures);
    void init();
    void draw(sf::RenderWindow& window) const override;
    void update(float deltaTime);

    float getlinearAcc() const;
    void setLinearAcc(float linearAcc);
    void multiplyLinearAcc(float k);

private:
    float angBreakDecc_; // deg / s^2
    float angConstDecc_; // deg / s^2
    float linBreakDecc_; // pixels / s^2
    float linConstDecc_; // pixels / s^2

    float decelerationDivider_; // if (backward) acceleration /= decelerationDivider_;

    bool userInput_ = false;
    bool boostActive_ = false;
    bool brakeActive_ = false;

    sf::Sprite boostSprite_;
    sf::Sprite engineSprite_;

    const std::map<std::string, sf::Texture>& textures_;

    void userMovement(float deltaTime);
    void updateSprites();
    sf::Vector2f getInput();
    void calculateVelocity(const float& lin_acc, const float& theta_acc, const float& deltaTime);
    void calculateAngularVelocity(float theta_acc, float deltaTime);
    sf::Vector2f calculateDeceleration(float deltaTime);
    sf::Vector2f calculateBrakeDeceleration(float deltaTime);
};

#endif //SPACE_SHOOTER_PLAYER_H

#ifndef SPACE_SHOOTER_PLAYER_H
#define SPACE_SHOOTER_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <cmath>
#include <memory>

class Player : public Entity {
public:
    Player(sf::Vector2f spawn_point, const std::map<std::string, sf::Texture> &textures);
    void draw(sf::RenderWindow& window) const override;
    void update(float deltaTime, const sf::Vector2f& netForce);
    void updateSprites();
    void setNetForce(const sf::Vector2f& netForce);

private:
    float angBreakDecc_; // deg / s^2
    float angConstDecc_; // deg / s^2
    float linBreakDecc_; // pixels / s^2
    float linConstDecc_; // pixels / s^2

    bool userInput_;
    bool boostActive_;
    bool brakeActive_;
    sf::Vector2f netForce_;

    sf::Sprite boostSprite_;
    sf::Sprite engineSprite_;

    sf::Vector2f getInput();
    sf::Vector2f calculateDeceleration(float deceleration,float deltaTime);

    void updateVelocity(float deltaTime);
};

#endif //SPACE_SHOOTER_PLAYER_H

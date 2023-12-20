#ifndef SPACE_SHOOTER_OBJECT_H
#define SPACE_SHOOTER_OBJECT_H

#include <SFML/Graphics.hpp>
#include <cmath>
/*
 * Lin - linear; Ang - angular; Vel - velocity; Acc - acceleration; Rot - rotation; Pos - position
 */
class Object {
public:
    void setPos(const sf::Vector2f& newPos);
    sf::Vector2f getPos() const;

    void setRot(float newRot);
    float getRot() const;

    void setLinVel(const sf::Vector2f& newVel);
    sf::Vector2f getLinVel() const;

    void setLinAcc(float newAcc);
    float getLinAcc() const;

    void setAngVel(float newVel);
    float getAngVel() const;

    void setAngAcc(float newAcc);
    float getAngAcc() const;

    void setRadius(int newRadius);
    int getRadius() const;

    void setIsAlive(bool isAlive);
    bool getIsAlive() const;

    sf::FloatRect getBounds() const;

    const sf::Sprite& getSprite() const;

protected:
    void addSprite(const std::string&, const sf::Texture& texture);
    void calculateLinVel(float deltaTime);
    void calculateAngVel(float deltaTime);
    static sf::Vector2f vectorNormalize(const sf::Vector2f& vector);
    static float vectorLength(const sf::Vector2f& vec);
    sf::Vector2f calculateLinAccDirection() const;
    sf::Vector2f calculateLinAcc(sf::Vector2f accDirection, float deltaTime) const;    static void scaleSprite(sf::Sprite& sprite, const sf::Vector2f &factor);
    static void scaleSprite( sf::Sprite& sprite, float factorX, float factorY);
    void spriteInit(const std::map<std::string, sf::Texture> &textures);
    void spriteInit(const sf::Texture& texture);
    std::map<std::string, sf::Sprite> sprites_;
    sf::Sprite mainSprite_;

    sf::Vector2f linVel_; // pixels / s
    float linAcc_; // pixels / s^s
    float maxLinVel_; // pixels / s
    float maxLinAcc_; // pixels / s^s

    float angVel_; // deg / s
    float angAcc_; // deg / s^2
    float maxAngVel_; // deg / s
    float maxAngAcc_; // deg / s^s

    sf::Vector2f pos_; // pixels // TODO to uint?
    float rot_; // deg

    int radius_; // pixels

    bool alive_ = true;

    /// returns -> -1, 0, 1
    template<typename T>
    int getSign(T val) { return (T(0) < val) - (val < T(0)); }
};


#endif //SPACE_SHOOTER_OBJECT_H

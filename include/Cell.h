#ifndef SPACE_SHOOTER_CELL_H
#define SPACE_SHOOTER_CELL_H

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class Cell {
public:
    Cell()
            : player_(nullptr), enemies_(), playerBullets_(), enemyBullets_() {}
//    , planet_(nullptr)
    // Player
    bool hasPlayer() const;
    Player* getPlayer() const;
    void setPlayer(Player* player);

    // Enemies
    bool hasEnemies() const;
    const std::vector<Enemy*>& getEnemies() const;
    void addEnemy(Enemy* enemy);
    void removeEnemy(Enemy* enemy);

    // Player Bullets
    bool hasPlayerBullets() const;
    const std::vector<Bullet*>& getPlayerBullets() const;
    void addPlayerBullet(Bullet* bullet);
    void removePlayerBullet(Bullet* bullet);

    // Enemy Bullets
    bool hasEnemyBullets() const;
    const std::vector<Bullet*>& getEnemyBullets() const;
    void addEnemyBullet(Bullet* bullet);
    void removeEnemyBullet(Bullet* bullet);

//    // Planets
//    bool hasPlanet() const {
//        return planet_ != nullptr;
//    }
//
//    Planet* getPlanet() const {
//        return planet_;
//    }
//
//    void setPlanet(Planet* planet) {
//        planet_ = planet;
//    }

private:
    Player* player_;
    std::vector<Enemy*> enemies_;
    std::vector<Bullet*> playerBullets_;
    std::vector<Bullet*> enemyBullets_;
//    Planet* planet_;
};



#endif //SPACE_SHOOTER_CELL_H

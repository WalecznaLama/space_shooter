#ifndef SPACE_SHOOTER_CELL_H
#define SPACE_SHOOTER_CELL_H

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Planet.h"
#include "Powerup.h"

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

    // SpaceObject
    bool hasSpaceObjects() const;
    const std::vector<SpaceObject*>& getSpaceObjects() const;
    void addSpaceObject(SpaceObject* spaceObject);
    void removeSpaceObject(SpaceObject* spaceObject);

    bool isOccupied() const;
    bool isOccupiedEnemy() const;

private:
    Player* player_;
    std::vector<Enemy*> enemies_;
    std::vector<Bullet*> playerBullets_;
    std::vector<Bullet*> enemyBullets_;
    std::vector<Planet*> planets_;
    std::vector<SpaceObject*> spaceObjects_;
};



#endif //SPACE_SHOOTER_CELL_H

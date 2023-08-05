#include "Cell.h"

bool Cell::hasPlayer() const { return player_ != nullptr; }
Player *Cell::getPlayer() const  { return player_; }
void Cell::setPlayer(Player *player) { player_ = player; }

bool Cell::hasEnemies() const { return !enemies_.empty(); }
const std::vector<Enemy *> &Cell::getEnemies() const  { return enemies_; }
void Cell::addEnemy(Enemy *enemy) { enemies_.push_back(enemy); }
void Cell::removeEnemy(Enemy* enemy) { enemies_.erase(std::remove(enemies_.begin(), enemies_.end(),
                                                                  enemy), enemies_.end()); }
// Player Bullets
bool Cell::hasPlayerBullets() const { return !playerBullets_.empty(); }
const std::vector<Bullet*>& Cell::getPlayerBullets() const { return playerBullets_; }
void Cell::addPlayerBullet(Bullet* bullet) { playerBullets_.push_back(bullet); }
void Cell::removePlayerBullet(Bullet* bullet) { playerBullets_.erase(std::remove(playerBullets_.begin(),
                                                                                 playerBullets_.end(),bullet),
                                                                     playerBullets_.end()); }
// Enemy Bullets
bool Cell::hasEnemyBullets() const { return !enemyBullets_.empty(); }
const std::vector<Bullet*>& Cell::getEnemyBullets() const { return enemyBullets_; }
void Cell::addEnemyBullet(Bullet* bullet) { enemyBullets_.push_back(bullet); }
void Cell::removeEnemyBullet(Bullet* bullet) { enemyBullets_.erase(std::remove(enemyBullets_.begin(),
                                                                               enemyBullets_.end(), bullet),
                                                                   enemyBullets_.end()); }

bool Cell::isOccupied() const { return hasPlayer() || hasEnemies() || hasPlayerBullets() || hasEnemyBullets(); }
bool Cell::isOccupiedEnemy() const { return hasEnemies() || hasEnemyBullets(); }
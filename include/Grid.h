#ifndef SPACE_SHOOTER_GRID_H
#define SPACE_SHOOTER_GRID_H

#include "Cell.h"

class Grid {
public:
    Grid(int width, int height);
    Cell& getCell(int x, int y);
    void setCell(int x, int y, const Cell& cell);
    bool isInside(int x, int y) const;
    bool isInside(sf::Vector2f position) const;

private:
    int width_;
    int height_;
    std::vector<std::vector<Cell>> cells_;
};

#endif //SPACE_SHOOTER_GRID_H

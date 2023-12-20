#ifndef SPACE_SHOOTER_GRID_H
#define SPACE_SHOOTER_GRID_H

#include "Cell.h"
#include <algorithm> // std::find

class Grid {
public:
    Grid(int width, int height);
    Cell& getCell(sf::Vector2f position);
    std::vector<std::shared_ptr<Cell>> getCircleCells(sf::Vector2f position_offset, int radius);
    bool isInside(sf::Vector2f position) const;
    static const int PIXELS_PER_CELL;

private:
    int width_;
    int height_;
    std::vector<std::vector<Cell>> cells_;

    static const int SAMPLE_RATE_CIRCLE;
};

#endif //SPACE_SHOOTER_GRID_H

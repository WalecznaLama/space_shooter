#ifndef SPACE_SHOOTER_GRID_H
#define SPACE_SHOOTER_GRID_H

#include "Cell.h"
#include <algorithm> // std::find

class Grid {
public:
    Grid(int width, int height);
    Cell& getCell(sf::Vector2f position);
    bool isInside(sf::Vector2f position) const;
    sf::Vector2i getSize() const;
    sf::Vector2i getSizePixels() const;
    static const int PIXELS_PER_CELL;

private:
    int width_;
    int height_;
    std::vector<std::vector<Cell>> cells_;

    static const int SAMPLE_RATE_CIRCLE;
};

#endif //SPACE_SHOOTER_GRID_H

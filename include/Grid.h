#ifndef SPACE_SHOOTER_GRID_H
#define SPACE_SHOOTER_GRID_H

#include "Cell.h"
#include <algorithm> // std::find

class Grid {
public:
    Grid(int width, int height);
    Cell& getCell(sf::Vector2f position);
    std::vector<std::shared_ptr<Cell>> getCellsOnRadius(sf::Vector2f position, int radius);
    void setCell(sf::Vector2f position, const Cell& cell);
    bool isInside(sf::Vector2f position) const;
    static const int PIXELS_PER_CELL;

private:
    int width_;
    int height_;
    std::vector<std::vector<Cell>> cells_;

    static const int SAMPLE_RATE_CIRCLE;
    static std::vector<sf::Vector2i> circleCells(int radius);
};

#endif //SPACE_SHOOTER_GRID_H

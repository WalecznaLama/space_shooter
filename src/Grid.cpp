#include "Grid.h"

const int Grid::PIXELS_PER_CELL = 3;

Grid::Grid(int width, int height)
        : width_(width), height_(height) {
    // Initialize the grid with empty cells
    cells_ = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width));
}

Cell &Grid::getCell(int x, int y) { return cells_[y/PIXELS_PER_CELL][x/PIXELS_PER_CELL]; }

void Grid::setCell(int x, int y, const Cell &cell) { cells_[y/PIXELS_PER_CELL][x/PIXELS_PER_CELL] = cell; }

bool Grid::isInside(int x, int y) const {
    return x >= 0 && y >= 0 && x < width_*PIXELS_PER_CELL && y < height_*PIXELS_PER_CELL; }

bool Grid::isInside(sf::Vector2f position) const {
    return position.x >= 0 && position.y >= 0 && (position.x < width_*PIXELS_PER_CELL) && position.y < height_*PIXELS_PER_CELL;
}

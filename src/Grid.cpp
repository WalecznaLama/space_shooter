#include "Grid.h"

Grid::Grid(int width, int height)
        : width_(width), height_(height) {
    // Initialize the grid with empty cells
    cells_ = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width));
}

Cell &Grid::getCell(int x, int y) { return cells_[y][x]; }

void Grid::setCell(int x, int y, const Cell &cell) { cells_[y][x] = cell; }

bool Grid::isInside(int x, int y) const { return x >= 0 && y >= 0 && x < width_ && y < height_; }

bool Grid::isInside(sf::Vector2f position) const {
    return position.x >= 0 && position.y >= 0 && position.x < width_ && position.y < height_;
}

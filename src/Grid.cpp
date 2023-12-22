#include "Grid.h"

const int Grid::PIXELS_PER_CELL = 3;

Grid::Grid(int width, int height)
        : width_(width), height_(height) {
    // Initialize the grid with empty cells
    cells_ = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width));
}

Cell& Grid::getCell(sf::Vector2f position) {
    auto _position = sf::Vector2i(position);
    int y_pos = _position.y/PIXELS_PER_CELL;
    int x_pos = _position.x/PIXELS_PER_CELL;

    x_pos = std::min(x_pos, width_);
    x_pos = std::max(x_pos, 0);
    y_pos = std::min(y_pos, height_);
    y_pos = std::max(y_pos, 0);

    return cells_[y_pos][x_pos];
}

bool Grid::isInside(sf::Vector2f position) const {
    auto [x, y] = position;
    return x > 0 && y > 0 && x < width_*PIXELS_PER_CELL && y < height_*PIXELS_PER_CELL;
}

sf::Vector2i Grid::getSize() const {
    return { width_, height_ };
}

sf::Vector2i Grid::getSizePixels() const {
    return { width_*PIXELS_PER_CELL, height_*PIXELS_PER_CELL };
}

#include "Grid.h"

const int Grid::PIXELS_PER_CELL = 3;
const int Grid::SAMPLE_RATE_CIRCLE = 6;

Grid::Grid(int width, int height)
        : width_(width), height_(height) {
    // Initialize the grid with empty cells
    cells_ = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width));
}

Cell& Grid::getCell(sf::Vector2f position) {
    auto [x, y] = position;
    return cells_[y/PIXELS_PER_CELL][x/PIXELS_PER_CELL];
}

std::vector<std::shared_ptr<Cell>> Grid::getCircleCells(sf::Vector2f position_offset, int radius) {
    std::vector<sf::Vector2i> cell_poses;
    std::vector<std::shared_ptr<Cell>> cells;
    double thetaStep = 2 * M_PI / SAMPLE_RATE_CIRCLE;
    for (int i = 0; i < SAMPLE_RATE_CIRCLE; ++i) {
        double theta = i * thetaStep;
        int x = std::round(radius * cos(theta)) + position_offset.x;
        x /= PIXELS_PER_CELL;
        int y = std::round(radius * sin(theta)) + position_offset.y;
        y /= PIXELS_PER_CELL;

        if (y < 1 || y > height_ - 1 || x < 1 || x > width_- 1) {  // if not in borders
            return {};
        }

        sf::Vector2i pose = {x, y};
        if (std::find(cell_poses.begin(), cell_poses.end(),pose) == cell_poses.end()){ // find if pose exists current in vector
            cell_poses.emplace_back(pose);
            cells.emplace_back(std::make_shared<Cell>(cells_[pose.y][pose.x]));
        }
    }
    return cells;
}

bool Grid::isInside(sf::Vector2f position) const {
    auto [x, y] = position;
    return x > 0 && y > 0 && x < width_*PIXELS_PER_CELL && y < height_*PIXELS_PER_CELL;
}

#include "Grid.h"

const int Grid::PIXELS_PER_CELL = 3;
const int Grid::SAMPLE_RATE_CIRCLE = 10;

Grid::Grid(int width, int height)
        : width_(width), height_(height) {
    // Initialize the grid with empty cells
    cells_ = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width));
}

Cell& Grid::getCell(sf::Vector2f position) {
    auto [x, y] = position;
    return cells_[y/PIXELS_PER_CELL][x/PIXELS_PER_CELL];
}
// TODO
std::vector<std::shared_ptr<Cell>> Grid::getCellsOnRadius(sf::Vector2f position, int radius) {
    auto poses = Grid::circleCells(radius);
    std::vector<std::shared_ptr<Cell>> cells;
    for (auto& pose : poses) {
        // Sprawdź, czy pozycja mieści się w granicach siatki
        if (pose.y >= 0 && pose.y < cells_.size() && pose.x >= 0 && pose.x < cells_[pose.y].size()) {
            cells.emplace_back(std::make_shared<Cell>(cells_[pose.y][pose.x]));
        }
    }
    return cells;
}

void Grid::setCell(sf::Vector2f position, const Cell &cell) {
    auto [x, y] = position;
    cells_[y/PIXELS_PER_CELL][x/PIXELS_PER_CELL] = cell;
}

bool Grid::isInside(sf::Vector2f position) const {
    auto [x, y] = position;
    return x > 0 && y > 0 && x < width_*PIXELS_PER_CELL && y < height_*PIXELS_PER_CELL;
}

std::vector<sf::Vector2i> Grid::circleCells(int radius) {
    std::vector<sf::Vector2i> poses;
    double thetaStep = 2 * M_PI / SAMPLE_RATE_CIRCLE;

    for (int i = 0; i < SAMPLE_RATE_CIRCLE; ++i) {
        double theta = i * thetaStep;
        int x = round(radius * cos(theta)) / PIXELS_PER_CELL;
        int y = round(radius * sin(theta)) / PIXELS_PER_CELL;
        sf::Vector2i pose = {x, y};
        if (std::find(poses.begin(), poses.end(), pose) == poses.end()) poses.emplace_back(pose);
    }

    return poses;
}
#include <map.h>

Map::Map(int width, int height) : width(width), height(height), totalDensity(0), maxDensity(0)
{
    int scaledWidth = width / Config::MAP_SCALE;
    int scaledHeight  = height / Config::MAP_SCALE;

    grid = new int*[scaledHeight];
    for (int i = 0; i < scaledHeight; i++) {
        grid[i] = new int[scaledWidth];
        memset(grid[i], 0, sizeof(grid[0][0]) * scaledWidth);
    }   
}

void Map::increasePopulation(Stg::Pose pose)
{
    int x = pose.x / Config::MAP_SCALE + width / (2 * Config::MAP_SCALE);
    int y = pose.y / Config::MAP_SCALE + height / (2 * Config::MAP_SCALE);
    grid[y][x] ++;

    calculate();
}

void Map::decreasePopulation(Stg::Pose pose)
{
    int x = pose.x / Config::MAP_SCALE + width / (2 * Config::MAP_SCALE);
    int y = pose.y / Config::MAP_SCALE + height / (2 * Config::MAP_SCALE);
    grid[y][x] --;
    if (grid[y][x] < 0) {
        grid[y][x] = 0;
    }

    calculate();
}

int Map::getValue(Stg::Pose pose)
{
    int x = pose.x / Config::MAP_SCALE + width / (2 * Config::MAP_SCALE);
    int y = pose.y / Config::MAP_SCALE + height / (2 * Config::MAP_SCALE);
    return grid[y][x];
}

void Map::calculate()
{
    int scaledWidth = width / Config::MAP_SCALE;
    int scaledHeight  = height / Config::MAP_SCALE;

    this->totalDensity = 0;
    this->maxDensity = 0;
    for (int j = scaledHeight - 1; j >= 0; --j) {
        for (int i = 0; i < scaledWidth; ++i) {
            if (grid[j][i] > this->maxDensity) {
                this->maxDensity = grid[j][i];
            }

            this->totalDensity += grid[j][i];
        }
    }
}

void Map::print()
{
    int scaledWidth = width / Config::MAP_SCALE;
    int scaledHeight  = height / Config::MAP_SCALE;

    for (int j = scaledHeight - 1; j >= 0; --j) {
        for (int i = 0; i < scaledWidth; ++i) {
            std::cout << grid[j][i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------" << std::endl;
}

#include <map.h>

Map::Map()
{
    memset(grid, 0, sizeof(grid[0][0]) * MAP_SIZE * MAP_SIZE);
}

void Map::increasePopulation(Stg::Pose pose)
{
    int x = pose.x / MAP_SCALE + MAP_SIZE / 2;
    int y = pose.y / MAP_SCALE + MAP_SIZE / 2;
    grid[x][y] ++;
}

void Map::decreasePopulation(Stg::Pose pose)
{
    int x = pose.x / MAP_SCALE + MAP_SIZE / 2;
    int y = pose.y / MAP_SCALE + MAP_SIZE / 2;
    grid[x][y] --;
}

int Map::getValue(Stg::Pose pose)
{
    int x = pose.x / MAP_SCALE + MAP_SIZE / 2;
    int y = pose.y / MAP_SCALE + MAP_SIZE / 2;
    return grid[x][y];
}

void Map::print()
{
    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------" << std::endl;
}

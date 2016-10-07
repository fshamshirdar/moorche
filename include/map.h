#ifndef MAP_H
#define MAP_H

#include <stage.hh>

// TODO: we need a dynamic map, using a hash instead of an array might be good!
#define MAP_SIZE 20
#define MAP_SCALE 1

class Map {
public:
    Map();

    void increasePopulation(Stg::Pose pose);
    void decreasePopulation(Stg::Pose pose);
    int getValue(Stg::Pose pose);

    void print();
private:
     int grid[MAP_SIZE][MAP_SIZE];
};

#endif // GRID_H

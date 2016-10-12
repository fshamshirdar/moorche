#ifndef MAP_H
#define MAP_H

#include <stage.hh>
#include <config.h>

class Map {
public:
    Map(int width, int height);

    void increasePopulation(Stg::Pose pose);
    void decreasePopulation(Stg::Pose pose);
    int getValue(Stg::Pose pose);

    void print();
private:
     int** grid;
     int width;
     int height;
};

#endif // GRID_H
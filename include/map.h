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
    int getTotalDensity() { return this->totalDensity; }
    int getMaxDensity() { return this->maxDensity; }
    void calculate();

    void print();
private:
     int** grid;
     int width;
     int height;
     int totalDensity;
     int maxDensity;
};

#endif // GRID_H

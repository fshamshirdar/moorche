#ifndef COLONY_H
#define COLONY_H

#include <stage.hh>
#include <string>
#include <sstream>
#include <fstream>
#include <map.h>
#include <moorche.h>
#include <trail.h>

class Moorche;
class Trail;

class Colony
{
public:
    Colony();
    ~Colony();

    Stg::Model* getSource() { return source; }
    std::vector<Stg::Model*> getFoods() { return foods; }
    Stg::Model* getFood(int i) { return foods.at(i); }
    Trail* getTrail() { return trail; }
    Map* getMap() { return map; }
    void setCycle(uint64_t cycle) { this->cycle = cycle; }
    uint64_t getCycle() { return this->cycle; }

    // counts the number of foods collected from each source
    void increaseFood(unsigned int foodIndex) { this->foodsCollected[foodIndex]++; }
    void printFoodCount();

    void connect(Stg::World* world);
    static int updateCallback(Stg::World* world, void* arg);
    void run(Stg::World* world);

private:
    unsigned int size;
    Map* map;
    std::vector<Moorche> moors;
    Trail* trail;
    uint64_t cycle;
    Stg::Model *source;
    std::vector<Stg::Model*> foods;
    // counts the number of foods collected from each source
    uint64_t *foodsCollected;

    std::ofstream logFile;
};

#endif // COLONY_H

#ifndef COLONY_H
#define COLONY_H

#include <stage.hh>
#include <string>
#include <sstream>
#include <map.h>
#include <moorche.h>
#include <trail.h>

class Moorche;
class Trail;

class Colony
{
public:
    Colony(unsigned int populationSize);
    ~Colony();

    Stg::Model* getSource() { return source; }
    Stg::Model* getFood() { return food; }
    Trail* getTrail() { return trail; }
    Map* getMap() { return map; }
    void setCycle(uint64_t cycle) { this->cycle = cycle; }
    uint64_t getCycle() { return this->cycle; }

    void connect(Stg::World* world);
    static int updateCallback(Stg::World* world, void* arg);
    void run(Stg::World* world);

private:
    unsigned int size;
    Map* map;
    Moorche* moors;
    Trail* trail;
    uint64_t cycle;
    Stg::Model *source, *food;
};

#endif // COLONY_H

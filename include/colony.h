#ifndef COLONY_H
#define COLONY_H

#include <stage.hh>
#include <string>
#include <sstream>
#include <include/moorche.h>
#include <include/trail.h>

class Moorche;

class Colony
{
public:
    Colony(unsigned int populationSize);
    ~Colony();

    Stg::Model* getSource() { return source; }
    Stg::Model* getFood() { return food; }
    Trail* getTrail() { return trail; }
    void setCycle(uint64_t cycle) { this->cycle = cycle; }
    uint64_t getCycle() { return this->cycle; }

    void connect(Stg::World* world);
    static int updateCallback(Stg::World* world, void* arg);
    void run(Stg::World* world);

private:
    unsigned int size;
    Moorche* moors;
    Trail* trail;
    uint64_t cycle;
    Stg::Model *source, *food;
};

#endif // COLONY_H

#ifndef COLONY_H
#define COLONY_H

#include <stage.hh>
#include <string>
#include <sstream>
#include <include/moorche.h>

class Colony
{
public:
    Colony(unsigned int populationSize);
    ~Colony();
    void connect(Stg::World* world);
    static int updateCallback(Stg::World* world, void* arg);
    void run(Stg::World* world);

private:
    unsigned int size;
    Moorche* moors;
};

#endif // COLONY_H

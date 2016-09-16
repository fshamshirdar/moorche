#ifndef COLONY_H
#define COLONY_H

#include <stage.hh>
#include <string>
#include <sstream>
#include <include/moorche.h>

class Moorche;

class Colony
{
public:
    Colony(unsigned int populationSize);
    ~Colony();

    Stg::Model* getSource() { return source; }
    Stg::Model* getFood() { return food; }

    void connect(Stg::World* world);
    static int updateCallback(Stg::World* world, void* arg);
    void run(Stg::World* world);

private:
    unsigned int size;
    Moorche* moors;
    Stg::Model *source, *food;
};

#endif // COLONY_H

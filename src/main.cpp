#include <iostream>
#include <stage.hh>
#include <include/colony.h>

int main(int argc, char** argv)
{
    char* worldPath = "/home/faraz/workspace/cmpt882/moorche/worlds/simple.world";
    unsigned int populationSize = 10;

    // check and handle the argumets
//    if (argc < 3) {
//        puts( "Usage: stest <worldfile> <number of robots>" );
//        exit(0);
//    }

    // initialize libstage
    Stg::Init(&argc, &argv);

    // create the world
    // Stg::World world;
    Stg::WorldGui world(800, 700, "Moorche");
    world.Load(worldPath);

    Colony* colony = new Colony(populationSize);
    colony->connect(&world);

    // and then run the simulation
    world.Run();

    return 0;
}

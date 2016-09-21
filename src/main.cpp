#include <iostream>
#include <stage.hh>
#include <colony.h>

int main(int argc, char** argv)
{
    // char* worldPath = "/Users/farazshamshirdar/workspace/autonomylab/moorche/worlds/simple.world";
    // unsigned int populationSize = 7;

    // check and handle the argumets
    if (argc < 3) {
        puts( "Usage: moorche <worldfile> <number of robots>" );
        exit(0);
    }

    // initialize libstage
    Stg::Init(&argc, &argv);

    // create the world
    // Stg::World world;
    Stg::WorldGui world(800, 700, "Moorche");
    world.Load(argv[1]);

    Colony* colony = new Colony(atoi(argv[2]));
    colony->connect(&world);

    // and then run the simulation
    world.Run();

    return 0;
}

#include <iostream>
#include <stage.hh>

int main(int argc, char** argv)
{
    char* worldPath = "/home/faraz/workspace/stage/src/worlds/simple.world";

    // check and handle the argumets
//    if (argc < 3) {
//        puts( "Usage: stest <worldfile> <number of robots>" );
//        exit(0);
//    }

    // initialize libstage
    Stg::Init(&argc, &argv);

    // create the world
    // Stg::World world;
    Stg::WorldGui world(800, 700, "Stage Benchmark Program");
    world.Load(worldPath);

    // and then run the simulation
    world.Run();

    return 0;
}

#include <colony.h>

Colony::Colony(unsigned int populationSize) : size(populationSize), moors(new Moorche[size]), trail(new Trail(this))
{
    // Debug Data
    std::vector<Stg::Pose> poses;
    poses.push_back(Stg::Pose(2.0, -2.0, 0.0, M_PI_4));
    poses.push_back(Stg::Pose(1.5, -1.5, 0.0, M_PI_4));
    poses.push_back(Stg::Pose(1.0, -1.0, 0.0, M_PI_4));
    poses.push_back(Stg::Pose(0.5, -0.5, 0.0, M_PI_4));
    poses.push_back(Stg::Pose(-0.0, -0.0, 0.0, M_PI_4));
    poses.push_back(Stg::Pose(-0.5, 0.5, 0.0, M_PI_4));
    poses.push_back(Stg::Pose(-1.0, 1.0, 0.0, M_PI_4));
    poses.push_back(Stg::Pose(-1.5, 1.5, 0.0, M_PI_4));
    poses.push_back(Stg::Pose(-2.0, 2.0, 0.0, M_PI_4));
//    trail->addPoints(poses, false);
}

Colony::~Colony()
{
    delete[] moors;
    delete trail;
    delete map;
}

void Colony::connect(Stg::World* world)
{
    this->source = world->GetModel("source_0");
    this->food = world->GetModel("food_0");

    map = new Map(world->GetModel("cave")->GetGeom().size.x, world->GetModel("cave")->GetGeom().size.y);

    for(unsigned int idx = 0; idx < size; idx++) {
        // the robots' models are named r0 .. r1999
        std::stringstream name;
        name << "r" << idx;

        moors[idx].setColony(this);

        // get the robot's model and subscribe to it
        Stg::ModelPosition* position = reinterpret_cast<Stg::ModelPosition*>(world->GetModel(name.str()));
        assert(position != 0);
        moors[idx].setPosition(position);

        // get the robot's ranger model and subscribe to it
        Stg::ModelRanger* ranger = reinterpret_cast<Stg::ModelRanger*>(moors[idx].getPosition()->GetChild("ranger:0"));
        assert(ranger != 0);
        moors[idx].setRanger(ranger);

        // Subscribe to models
        moors[idx].subscribe();
    }

    // register with the world
    world->AddUpdateCallback(Colony::updateCallback, reinterpret_cast<void*>(this));
}

int Colony::updateCallback(Stg::World* world, void* arg)
{
    Colony* colony = reinterpret_cast<Colony*>(arg);
    colony->run(world);
    // never remove this callback
    return 0;
}

void Colony::run(Stg::World *world)
{
    setCycle(world->GetUpdateCount());
    trail->update(getCycle());
    for (int idx = 0; idx < size; ++idx) {
        moors[idx].desicion(world);
    }


    if (getCycle() % 100 == 0) {
        map->print();
    }
}

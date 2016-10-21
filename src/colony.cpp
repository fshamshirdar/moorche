#include <colony.h>

Colony::Colony() : size(0), trail(new Trail(this))
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
    delete trail;
    delete map;
}

void Colony::connect(Stg::World* world)
{
    this->source = world->GetModel("source_0");

    int i = 0;
    std::stringstream foodName;
    foodName << "food_" << i;
    while (world->GetModel(foodName.str())) {
        this->foods.push_back(world->GetModel(foodName.str()));
        foodName.str("");
        foodName << "food_" << ++i;
    }

    map = new Map(world->GetModel("cave")->GetGeom().size.x, world->GetModel("cave")->GetGeom().size.y);

    i = 0;
    std::stringstream name;
    name << "r" << i;
    while (world->GetModel(name.str())) {
        moors.push_back(Moorche());

        // the robots' models are named r0 .. r1999
        moors[i].setColony(this);

        // get the robot's model and subscribe to it
        Stg::ModelPosition* position = reinterpret_cast<Stg::ModelPosition*>(world->GetModel(name.str()));
        assert(position != 0);
        moors[i].setPosition(position);

        // get the robot's ranger model and subscribe to it
        Stg::ModelRanger* ranger = reinterpret_cast<Stg::ModelRanger*>(moors[i].getPosition()->GetChild("ranger:0"));
        assert(ranger != 0);
        moors[i].setRanger(ranger);

        // Subscribe to models
        moors[i].subscribe();

        name.str("");
        name << "r" << ++i;
    }
    size = i;

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

    if (getCycle() % 1000 == 0) {
        map->print();
    }
}

#include <include/moorche.h>
#include <iostream>

Moorche::Moorche()
{
}

void Moorche::subscribe()
{
    this->position->Subscribe();
    this->ranger->Subscribe();
}

bool Moorche::moveToPose(Stg::Pose targetPose)
{
    double forwardSpeed = 0;
    double sideSpeed = 0;
    double turnSpeed = 0;

    Stg::Pose pose = getPosition()->GetPose();
    Stg::Pose line(targetPose.x - pose.x, targetPose.y - pose.y, 0, 0);

    if (line.y != 0) {
        turnSpeed = std::atan2(line.y, line.x) - pose.a;
    }

    std::cout << turnSpeed << std::endl;

    setSpeed(0, 0, turnSpeed);

    return true;
}

void Moorche::desicion(Stg::World *world)
{
    setLastVelocity(getPosition()->GetVelocity());
    moveToPose(getColony()->getSource()->GetPose());
}

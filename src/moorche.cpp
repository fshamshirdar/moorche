#include <include/moorche.h>
#include <iostream>

Moorche::Moorche() : currentState(Moorche::GO_TO_SOURCE)
{
}

void Moorche::subscribe()
{
    this->position->Subscribe();
    this->ranger->Subscribe();
}

bool Moorche::moveToPose(Stg::Pose targetPose)
{
    setLastVelocity(getPosition()->GetVelocity());

    const double distanceThrd = 0.1;
    const double angleThrd = 0.1;
    const double turnSpeedCoef = 4.0;

    double forwardSpeed = 0.0;
    double sideSpeed = 0.0;
    double turnSpeed = 0.0;

    Stg::Pose pose = getPosition()->GetPose();
    Stg::Pose line(targetPose.x - pose.x, targetPose.y - pose.y, 0, 0);

    if (line.y != 0) {
        double angleDiff = (std::atan2(line.y, line.x) - pose.a - targetPose.a);
        turnSpeed = angleDiff * turnSpeedCoef;
    }

    if (pose.Distance(targetPose) > distanceThrd) {
        forwardSpeed = 0.4;
    } else {
        turnSpeed = 0.0;
    }

    setSpeed(forwardSpeed, 0, turnSpeed);

    return true;
}

bool Moorche::randomMove()
{
    srand(time(0));
    setSpeed(0.4, 0, (rand() % 2 == 0) ? (rand() % 2) : ());
    return true;
}

void Moorche::desicion(Stg::World *world)
{
    switch (currentState) {
        case Moorche::GO_TO_SOURCE:
            if (getPosition()->GetPose().Distance(getColony()->getSource()->GetPose()) < 0.1) {
                currentState = Moorche::SEARCH_FOR_FOOD;
            } else {
                moveToPose(getColony()->getSource()->GetPose());
            }
            break;
        case Moorche::SEARCH_FOR_FOOD:
            if (getPosition()->GetPose().Distance(getColony()->getFood()->GetPose()) < 0.8) {
                currentState = Moorche::GO_TO_FOOD;
            } else {
                randomMove();
            }
            break;
        case Moorche::GO_TO_FOOD:
            if (getPosition()->GetPose().Distance(getColony()->getFood()->GetPose()) < 0.1) {
                currentState = Moorche::GO_TO_SOURCE;
            } else {
                moveToPose(getColony()->getFood()->GetPose());
            }
            break;
        default:
            break;
    }
}

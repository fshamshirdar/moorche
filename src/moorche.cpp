#include <include/moorche.h>

Moorche::Moorche()
{
}

void Moorche::setPosition(Stg::ModelPosition *position)
{
    this->position = position;
}

Stg::ModelPosition* Moorche::getPosition()
{
    return this->position;
}

void Moorche::subscribePosition()
{
    this->position->Subscribe();
}

void Moorche::setSpeed(double forwardSpeed, double sideSpeed, double turnSpeed)
{
    this->position->SetSpeed(forwardSpeed, sideSpeed, turnSpeed);
}

void Moorche::setRanger(Stg::ModelRanger* ranger)
{
    this->ranger = ranger;
}

Stg::ModelRanger* Moorche::getRanger()
{
    return this->ranger;
}

void Moorche::subscribeRanger()
{
    this->ranger->Subscribe();
}

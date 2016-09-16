#include <include/moorche.h>
#include <iostream>

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

void Moorche::subscribe()
{
    this->position->Subscribe();
    this->ranger->Subscribe();
}

void Moorche::desicion(Stg::World *world)
{
    setSpeed(0, 0, 1);
}

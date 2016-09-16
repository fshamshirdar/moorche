#ifndef MOORCHE_H
#define MOORCHE_H

#include <stage.hh>
#include <include/colony.h>

class Colony;

class Moorche
{
public:
    enum State {
       GO_TO_SOURCE,
       SEARCH_FOR_FOOD,
       GO_TO_FOOD
    };

public:
    Moorche();
    void setColony(Colony* colony) { this->colony = colony; }
    Colony* getColony() { return colony; }

    // Positioning
    void setPosition(Stg::ModelPosition* position) { this->position = position; }
    Stg::ModelPosition* getPosition() { return position; }
    void setSpeed(double forwardSpeed, double sideSpeed, double turnSpeed) { position->SetSpeed(forwardSpeed, sideSpeed, turnSpeed); }

    // Ranger
    void setRanger(Stg::ModelRanger* ranger) { this->ranger = ranger; }
    Stg::ModelRanger* getRanger() { return ranger; }

    // Velocity
    void setLastVelocity(Stg::Velocity lastVelocity) { this->lastVelocity = lastVelocity; }
    Stg::Velocity getLastVelocity() { return lastVelocity; }

    // Desicion
    void subscribe();
    void desicion(Stg::World* world);

private:
    bool moveToPose(Stg::Pose targetPose);
    bool randomMove();

private:
    Stg::ModelPosition* position;
    Stg::ModelRanger* ranger;
    Stg::Velocity lastVelocity;
    Colony* colony;
    Moorche::State currentState;
};

#endif // MOORCHE_H

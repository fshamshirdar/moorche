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
       MOVE_FOOD_TO_SOURCE,
       GO_TO_FOOD
    };

public:
    Moorche();
    ~Moorche();
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

    // Cycle
    void setCycle(uint64_t cycle) { this->cycle = cycle; }
    uint64_t getCycle() { return this->cycle; }

    // Desicion
    void subscribe();
    void desicion(Stg::World* world);

private:
    void moveToPose(Stg::Pose targetPose);
    void randomMove();
    void calculateDistances();

private:
    Stg::ModelPosition* position;
    Stg::ModelRanger* ranger;
    Stg::Velocity lastVelocity;
    Colony* colony;
    Moorche::State currentState;
    uint64_t cycle;

    double forward_distance;
    double left_distance;
    double right_distance;
    double average_left_distance;
    double average_right_distance;
};

#endif // MOORCHE_H

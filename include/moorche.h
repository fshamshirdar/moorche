#ifndef MOORCHE_H
#define MOORCHE_H

#include <stage.hh>
#include <colony.h>
#include <config.h>

class Colony;

class Moorche
{
public:
    enum State {
       GO_TO_SOURCE,
       SEARCH_FOR_FOOD,
       MOVE_FOOD_TO_SOURCE,
       GO_TO_FOOD,
       OBSTACLE_AVOIDANCE
    };

public:
    Moorche();
    ~Moorche();
    void setColony(Colony* colony) { this->colony = colony; }
    Colony* getColony() { return colony; }

    // State
    void setState(Moorche::State state);
    State getState() { return this->currentState; }

    // Positioning
    void setPosition(Stg::ModelPosition* position) { this->position = position; }
    Stg::ModelPosition* getPosition() { return position; }
    bool inZone(Stg::Model* model);
    double getModelRadius(Stg::Model* model);
    void setSpeed(double forwardSpeed, double sideSpeed, double turnSpeed);
    void setSpeed(Stg::Velocity vel);

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
    void moveToPose(Stg::Pose targetPose);
    void randomMove();
    void calculateDistances();

private:
    Stg::ModelPosition* position;
    Stg::ModelRanger* ranger;
    Stg::Velocity lastVelocity;
    Colony* colony;
    Moorche::State currentState;
    Moorche::State lastState;
    std::vector<Stg::Pose> temporaryTrail;
    int obstacleAvoidanceCycle;
    int chosenFood;

    double forward_distance;
    double left_distance;
    double right_distance;
    double average_left_distance;
    double average_right_distance;
};

#endif // MOORCHE_H

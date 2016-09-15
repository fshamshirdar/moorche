#ifndef MOORCHE_H
#define MOORCHE_H

#include <stage.hh>

class Moorche
{
public:
    Moorche();

    // Positioning
    void setPosition(Stg::ModelPosition* position);
    Stg::ModelPosition* getPosition();
    void subscribePosition();
    void setSpeed(double forwardSpeed, double sideSpeed, double turnSpeed);

    // Ranger
    void setRanger(Stg::ModelRanger* ranger);
    Stg::ModelRanger* getRanger();
    void subscribeRanger();

private:
    Stg::ModelPosition* position;
    Stg::ModelRanger* ranger;
};

#endif // MOORCHE_H

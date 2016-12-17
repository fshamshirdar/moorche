#include <moorche.h>
#include <iostream>

Moorche::Moorche() : currentState(Moorche::GO_TO_SOURCE), lastState(Moorche::GO_TO_SOURCE), obstacleAvoidanceCycle(0), chosenFood(0), additionalTurnSpeed(0.0), assignedFoodId(-1)
{
    srand(time(0));
}

Moorche::~Moorche()
{

}

void Moorche::subscribe()
{
    this->position->Subscribe();
    this->ranger->Subscribe();
}

void Moorche::setSpeed(double forwardSpeed, double sideSpeed, double turnSpeed)
{
    if (forwardSpeed > 0.0) {
        if (getColony()->getCycle() % Config::TRAIL_UPDATE_MODE_CYCLE == 0) {
            getColony()->getMap()->increasePopulation(this->getPosition()->GetPose());
            temporaryTrail.push_back(this->getPosition()->GetPose());
        }
    }

    getPosition()->SetSpeed(forwardSpeed, sideSpeed, turnSpeed);
    setLastVelocity(getPosition()->GetVelocity());
}

void Moorche::setSpeed(Stg::Velocity vel)
{
    setSpeed(vel.x, vel.y, vel.a);
}

void Moorche::moveToPose(Stg::Pose targetPose)
{
    const double distanceThrd = 0.1;
    const double angleThrd = 0.1;
    const double turnSpeedCoef = 1.0;

    double forwardSpeed = 0.0;
    double turnSpeed = 0.0;

    Stg::Pose pose = getPosition()->GetPose();
    Stg::Pose line(targetPose.x - pose.x, targetPose.y - pose.y, 0, 0);

    if (line.y != 0) {
        double angleDiff = (std::atan2(line.y, line.x) - pose.a - targetPose.a);
        if (angleDiff > M_PI) {
            angleDiff -= 2 * M_PI;
        } else if (angleDiff < -M_PI) {
            angleDiff += 2 * M_PI;
        }
        turnSpeed = angleDiff * turnSpeedCoef;
    }

    if (pose.Distance(targetPose) > distanceThrd) {
        forwardSpeed = 0.4;
    } else {
        turnSpeed = 0.0;
    }

    if (turnSpeed >= angleThrd) {
        forwardSpeed = 0.0;
    }

    const double forward_distance_thrd = Config::FORWARD_DISTANCE_THRD;
    const double left_distance_thrd = Config::LEFT_DISTANCE_THRD;
    const double right_distance_thrd = Config::RIGHT_DISTANCE_THRD;

    if (forward_distance < forward_distance_thrd) {
        forwardSpeed = 0.1;
        if (average_right_distance < average_left_distance) {
            turnSpeed = -1.0;
        } else {
            turnSpeed = 1.0;
        }
    } else if (left_distance < left_distance_thrd) {
        if (right_distance < left_distance) {
            forwardSpeed = -0.1; // move backward
        } else {
            turnSpeed = 1.0;
            forwardSpeed = 0.1;
        }
    } else if (right_distance < right_distance_thrd) {
        if (left_distance < right_distance) {
            forwardSpeed = -0.1; // move backward
        } else {
            turnSpeed = -1.0;
            forwardSpeed = 0.1;
        }
    }

    setSpeed(forwardSpeed, 0, turnSpeed);
}

void Moorche::randomMove()
{
    int turnSide = 0;
    const double turnSpeedCoef = Config::TURN_SPEED_COEF;
    double turnSpeed = 0;
    double forwardSpeed = Config::DEFAULT_FORWARD_SPEED;

    const double forward_distance_thrd = Config::FORWARD_DISTANCE_THRD;
    const double left_distance_thrd = Config::LEFT_DISTANCE_THRD;
    const double right_distance_thrd = Config::RIGHT_DISTANCE_THRD;

    if (forward_distance < forward_distance_thrd) {
        forwardSpeed = 0.1;
        if (average_right_distance < average_left_distance) {
            turnSide = -1;
        } else {
            turnSide = 1;
        }

    } else if (left_distance < left_distance_thrd) {
        if (right_distance < left_distance) {
            forwardSpeed = -0.1; // move backward
        } else {
            turnSide = 1;
            forwardSpeed = 0.1;
        }
    } else if (right_distance < right_distance_thrd) {
        if (left_distance < right_distance) {
            forwardSpeed = -0.1; // move backward
        } else {
            turnSide = -1;
            forwardSpeed = 0.1;
        }
    }

    turnSpeed = turnSide * turnSpeedCoef;
    if (turnSide == 0) {
        Trail::Point* targetPoint = getColony()->getTrail()->getBestPointInCircle(getPosition()->GetPose(), assignedFoodId, Config::ROBOT_TRAIL_RADIUS, (currentState == Moorche::MOVE_FOOD_TO_SOURCE));
        double prob = (double)(rand() % 100) / 100.0;
        if (targetPoint && prob < Config::ALPHA) {
            double followingTrailAngle = 0.0;
            double angleToTarget = atan2((targetPoint->getPose().y - getPosition()->GetPose().y), (targetPoint->getPose().x - getPosition()->GetPose().x));
            double angleDiff = (targetPoint->getPose().a - getPosition()->GetPose().a);
            if (targetPoint->getPose().x != getPosition()->GetPose().x) {
                // followingTrailAngle = angleDiff + (angleToTarget / 4); // worse results
                followingTrailAngle = angleToTarget - getPosition()->GetPose().a;
            } else {
                followingTrailAngle = angleDiff;
            }

            if (followingTrailAngle > M_PI) {
                followingTrailAngle -= 2 * M_PI;
            } else if (followingTrailAngle < -M_PI) {
                followingTrailAngle += 2 * M_PI;
            }

            double additionalAngle = 0.0; // SO_LOST
            Trail::Point* otherPoint = getColony()->getTrail()->getBestPointInCircle(targetPoint->getPose(), assignedFoodId, Config::MIN_DISTANCE_BETWEEN_TRAILS, (currentState != Moorche::MOVE_FOOD_TO_SOURCE));
            if (otherPoint && otherPoint->getPose().Distance(targetPoint->getPose()) < Config::MIN_DISTANCE_BETWEEN_TRAILS && targetPoint->getPose().x != otherPoint->getPose().x) {
                double trailsAngle = atan2((targetPoint->getPose().y - otherPoint->getPose().y), (targetPoint->getPose().x - otherPoint->getPose().x));
                additionalAngle = (M_PI - trailsAngle) / 5.0;
            }

            if (additionalAngle > M_PI) {
                additionalAngle -= 2 * M_PI;
            } else if (additionalAngle < -M_PI) {
                additionalAngle += 2 * M_PI;
            }

            followingTrailAngle += additionalAngle;

            if (followingTrailAngle > M_PI) {
                followingTrailAngle -= 2 * M_PI;
            } else if (followingTrailAngle < -M_PI) {
                followingTrailAngle += 2 * M_PI;
            }
            // std::cout << "SO_LOST " << additionalAngle << std::endl;

            turnSpeed += turnSpeedCoef * followingTrailAngle;
        } else {
            if (getColony()->getCycle() % Config::RANDOM_DECISION_MODE_CYCLE == 0) {
                if (turnSide == 0) { // Obstacle Avoidance
                    turnSide = (rand() % 2 == 0) ? -1 : 1;
                }
                additionalTurnSpeed = turnSide * ((double)rand() / RAND_MAX);
            }
            turnSpeed += additionalTurnSpeed;
        }
    }

    setSpeed(forwardSpeed, 0, turnSpeed);
}

void Moorche::calculateDistances()
{
    Stg::ModelRanger::Sensor sensor = getRanger()->GetSensors()[0];

    const unsigned int left_idx_start = Config::LEFT_IDX_START;
    const unsigned int left_idx_end = Config::LEFT_IDX_END;
    const unsigned int forward_idx_start = Config::FORWARD_IDX_START;
    const unsigned int forward_idx_end = Config::FORWARD_IDX_END;
    const unsigned int right_idx_start = Config::RIGHT_IDX_START;
    const unsigned int right_idx_end = Config::RIGHT_IDX_END;

    forward_distance = 1000.0;
    left_distance = 1000.0;
    right_distance = 1000.0;
    average_left_distance = 0.0;
    average_right_distance = 0.0;

    for (unsigned int idx = 0; idx < sensor.ranges.size(); idx ++) {
        if (idx > forward_idx_start && idx < forward_idx_end) {
            if (sensor.ranges[idx] < forward_distance) {
                forward_distance = sensor.ranges[idx];
            }
        }

        if (idx > left_idx_start && idx < left_idx_end) {
            average_left_distance += sensor.ranges[idx];
            if (sensor.ranges[idx] < left_distance) {
                left_distance = sensor.ranges[idx];
            }
        }

        if (idx > right_idx_start && idx < right_idx_end) {
            average_right_distance += sensor.ranges[idx];
            if (sensor.ranges[idx] < right_distance) {
                right_distance = sensor.ranges[idx];
            }
        }
    }

    average_left_distance = average_left_distance / (left_idx_end - left_idx_start);
    average_right_distance = average_right_distance / (right_idx_end - right_idx_start);
}

bool Moorche::inZone(Stg::Model *model)
{
    return (fabs(getPosition()->GetPose().x - model->GetPose().x) < model->GetGeom().size.x / 2 &&
            fabs(getPosition()->GetPose().y - model->GetPose().y) < model->GetGeom().size.y / 2);
}

double Moorche::getModelRadius(Stg::Model* model)
{
    return sqrt(pow(model->GetGeom().size.x, 2) + pow(model->GetGeom().size.y, 2));
}

void Moorche::setState(Moorche::State state)
{
    lastState = currentState;
    currentState = state;
}

void Moorche::assigningFood()
{
    int id = -1;
    double min_congestion_factor = Config::MAX_CONGESTION_FACTOR; //1;
    double robotSize = (getPosition()->GetGeom().size.x > getPosition()->GetGeom().size.y) ? getPosition()->GetGeom().size.x : getPosition()->GetGeom().size.y;
    // find what is the congestion factor of previous assigned food source3 (to decide whether to change food or not)
    double previous_food_congestion_factor = Config::MAX_CONGESTION_FACTOR;
    
    std::vector<int> knownFoodsId = getColony()->getKnownFoodsId();
    for (std::vector<int>::const_iterator it = knownFoodsId.begin(); it != knownFoodsId.end(); it++) {
        // std::cout << "Food: " << *it << " Point: ";
        Trail::Point* point = getColony()->getTrail()->getBestPointInCircle(getColony()->getSource()->GetPose(), (*it), Config::ROBOT_TRAIL_RADIUS, false);
        // std::cout << point << std::endl;
        if (point != NULL) {
            double congestion_factor = (2 * robotSize + Config::FORWARD_DISTANCE_THRD) * getColony()->getNoOfRobots(*it) / point->getDistanceToTarget();
            // std::cout << congestion_factor << " ";
            if (congestion_factor < min_congestion_factor) {
                id = (*it);
                min_congestion_factor = congestion_factor;
            }

            if (*it == assignedFoodId) {
                previous_food_congestion_factor = congestion_factor;
            }
        }
    }
    if ( (assignedFoodId != -1) && (assignedFoodId != id) ) {
        // switch to another food only if better than the previous food by a threshold
        if ( (previous_food_congestion_factor - min_congestion_factor) > Config::CONGESTION_SWITCHING_THRESHOLD ) {
            assignedFoodId = id;
        }
    } else {
        assignedFoodId = id;
    }

    if (assignedFoodId != -1) {
        getColony()->increaseNoOfRobots(assignedFoodId);
    }
    
    std::cout << "Robot assigned to " << assignedFoodId << " previous food congestion " << previous_food_congestion_factor << " min_congestion_factor " << min_congestion_factor << std::endl;
}

void Moorche::desicion(Stg::World *world)
{
    calculateDistances();
    switch (currentState) {
        case Moorche::GO_TO_SOURCE:
            if (inZone(getColony()->getSource())) {
                getPosition()->SetColor(Stg::Color::blue);
                currentState = Moorche::SEARCH_FOR_FOOD;
                if (temporaryTrail.size() < Config::MAX_TRAIL_SIZE && assignedFoodId >= 0) {
                    getColony()->getTrail()->addPoints(temporaryTrail, assignedFoodId, true);
                    // std::cout << "Trail to source updated: " << temporaryTrail.size() << std::endl;
                } else {
                    for (std::vector<Stg::Pose>::iterator it = temporaryTrail.begin(); it != temporaryTrail.end(); it ++) {
                        getColony()->getMap()->decreasePopulation((*it));
                    }
                }
 
                if (assignedFoodId != -1) {
                    getColony()->decreaseNoOfRobots(assignedFoodId);
                }
                assigningFood();
                temporaryTrail.clear();
            } else {
                moveToPose(getColony()->getSource()->GetPose());
            }
            break;
        case Moorche::SEARCH_FOR_FOOD:
            if (assignedFoodId == -1) {
                for (int i = 0; i < getColony()->getFoods().size(); i++) {
                    if (getPosition()->GetPose().Distance(getColony()->getFood(i)->GetPose()) < 2 * getModelRadius(getColony()->getFood(i))) {
                        currentState = Moorche::GO_TO_FOOD;
                        chosenFood = i;
                    } else {
                        randomMove();
                    }
                }
            } else {
                if (getPosition()->GetPose().Distance(getColony()->getFood(assignedFoodId)->GetPose()) < 2 * getModelRadius(getColony()->getFood(assignedFoodId))) {
                    currentState = Moorche::GO_TO_FOOD;
                    chosenFood = assignedFoodId;
                } else {
                    randomMove();
                }
            }
            break;
        case Moorche::GO_TO_FOOD:
            if (inZone(getColony()->getFood(chosenFood))) {
                // update food count
                getColony()->increaseFood(chosenFood);

                if (chosenFood == 0) {
                    getPosition()->SetColor(Stg::Color::red);
                } else if (chosenFood == 1) {
                    getPosition()->SetColor(Stg::Color::magenta);
                } else if (chosenFood == 2) {
                    getPosition()->SetColor(Stg::Color::cyan);
                } else if (chosenFood == 3) {
                    getPosition()->SetColor(Stg::Color::yellow);
                }

                getColony()->addFoodIdToKnownFoods(chosenFood);
                // getColony()->decreaseNoOfRobots(assignedFoodId);

                currentState = Moorche::MOVE_FOOD_TO_SOURCE;
                if (temporaryTrail.size() < Config::MAX_TRAIL_SIZE) {
                    getColony()->getTrail()->addPoints(temporaryTrail, chosenFood, false);
                    // std::cout << "Trail to food updated: " << temporaryTrail.size() << std::endl;
                } else {
                    for (std::vector<Stg::Pose>::iterator it = temporaryTrail.begin(); it != temporaryTrail.end(); it ++) {
                        getColony()->getMap()->decreasePopulation((*it));
                    }
                }
                temporaryTrail.clear();
            } else {
                moveToPose(getColony()->getFood(chosenFood)->GetPose());
            }
            break;
        case Moorche::MOVE_FOOD_TO_SOURCE:
            if (getPosition()->GetPose().Distance(getColony()->getSource()->GetPose()) < 2 * getModelRadius(getColony()->getSource())) {
                currentState = Moorche::GO_TO_SOURCE;
            } else {
                randomMove();
            }
            break;
        case Moorche::OBSTACLE_AVOIDANCE:
            setSpeed(getLastVelocity());
            obstacleAvoidanceCycle ++;
            if (obstacleAvoidanceCycle > 10) {
                obstacleAvoidanceCycle = 0;
                setState(lastState);
            }
        default:
            break;
    }
}

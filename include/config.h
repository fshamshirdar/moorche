#ifndef CONFIG_H
#define CONFIG_H

class Config
{
public:
    static const double EVAPORATION_COEFFICIENT_PER_CYCLE = 0.005;
    static const double ALPHA = 0.90;
    static const double ROBOT_TRAIL_RADIUS = 1.5;
    static const unsigned int TRAIL_UPDATE_MODE_CYCLE = 5;
    static const unsigned int RANDOM_DECISION_MODE_CYCLE = 5;
    static const double MIN_DISTANCE_BETWEEN_TRAILS = 0.75;
    static const double MAX_TRAIL_SIZE = 2000;
    static const double DEFAULT_FORWARD_SPEED = 0.4;
    static const double FORWARD_DISTANCE_THRD = 0.25;
    static const double LEFT_DISTANCE_THRD = 0.20;
    static const double RIGHT_DISTANCE_THRD = 0.20;
    static const double TURN_SPEED_COEF = 2.0;
    static const unsigned int LEFT_IDX_START = 0;
    static const unsigned int LEFT_IDX_END = 85;
    static const unsigned int FORWARD_IDX_START = 85;
    static const unsigned int FORWARD_IDX_END = 95;
    static const unsigned int RIGHT_IDX_START = 95;
    static const unsigned int RIGHT_IDX_END = 180;
    static const double MAP_SCALE = 0.25;
    static const double DENSITY_WEIGHT = 0.8;
    static const double STEPS_TO_TARGET_WEIGHT = 0.2;
};

#endif

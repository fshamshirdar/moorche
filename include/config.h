#ifndef CONFIG_H
#define CONFIG_H

class Config
{
public:
    static const double EVAPORATION_COEFFICIENT_PER_CYCLE = 0.0005;
    static const double ALPHA = 0.90;
    static const double MIN_DISTANCE_BETWEEN_TRAILS = 0.75;
    static const double MAX_TRAIL_SIZE = 2000;
};

#endif

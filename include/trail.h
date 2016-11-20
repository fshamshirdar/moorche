#ifndef TRAIL_H
#define TRAIL_H

#include <stage.hh>
#include <colony.h>
#include <config.h>

class Colony;

class Trail
{
public:
    class Point
    {
    public:
        Point(Stg::Pose pose, int foodId, uint64_t createCycle, double density, double distanceToTarget, int timesToTarget, int totalSteps, bool toSource);
        void update(uint64_t cycle);

        // Density
        void setDensity(double density) { this->density = density; }
        double getDensity() { return this->density; }

        // To Source
        void setToSource(bool toSource) { this->toSource = toSource; }
        bool isToSource() { return this->toSource; }

        // Times to Target
        void setTimesToTarget(int timesToTarget) { this->timesToTarget = timesToTarget; }
        int getTimesToTarget() { return this->timesToTarget; }

        // Total Steps
        void setTotalSteps(int totalSteps) { this->totalSteps = totalSteps; }
        int getTotalSteps() { return this->totalSteps; }

        // Distance to target
        void setDistanceToTarget(double distanceToTarget) { this->distanceToTarget = distanceToTarget; }
        double getDistanceToTarget() { return this->distanceToTarget; }

        Stg::Pose getPose() { return this->pose; }
        double getDistance(Stg::Pose target) { return this->pose.Distance(target); }

        int getFoodId() { return this->foodId; }

    private:
        Stg::Pose pose;
        uint64_t createdCycle;
        double density;
        bool toSource; // or to food
        int timesToTarget;
        int totalSteps;
        double distanceToTarget;
        int foodId;
    };

public:
    Trail(Colony* colony);
    void update(uint64_t cycle);
    void addPoints(std::vector<Stg::Pose> poses, int foodId, bool toSource);
    std::vector<Trail::Point*> getPoints() { return this->points; }
    Trail::Point* getClosestPoint(Stg::Pose pose);
    Trail::Point* getAveragePointInCircle(Stg::Pose pose, double radius, bool toSource);
    Trail::Point* getBestPointInCircle(Stg::Pose pose, int foodId, double radius, bool toSource);

    void print();

private:
    Colony* colony;
    std::vector<Trail::Point*> points;
    uint64_t cycle;
};

#endif

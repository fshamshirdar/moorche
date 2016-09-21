#ifndef TRAIL_H
#define TRAIL_H

#include <stage.hh>
#include <config.h>

class Trail
{
public:
    class Point
    {
    public:
        Point(Stg::Pose pose, uint64_t createCycle, double density, int timesToTarget, bool toSource);
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

        Stg::Pose getPose() { return this->pose; }
        double getDistance(Stg::Pose target) { return this->pose.Distance(target); }

    private:
        Stg::Pose pose;
        uint64_t createdCycle;
        double density;
        bool toSource; // or to food
        int timesToTarget;
    };

public:
    Trail();
    void update(uint64_t cycle);
    void addPoint(Stg::Pose pose);
    void addPoints(std::vector<Stg::Pose> poses, bool toSource);
    std::vector<Trail::Point*> getPoints() { return this->points; }
    Trail::Point* getClosestPoint(Stg::Pose pose);
    Trail::Point* getAveragePointInCircle(Stg::Pose pose, double radius, bool toSource);
    Trail::Point* getBestPointInCircle(Stg::Pose pose, double radius, bool toSource);

    void print();

private:
    std::vector<Trail::Point*> points;
    uint64_t cycle;
};

#endif

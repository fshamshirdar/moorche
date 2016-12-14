#ifndef SOURCE_H
#define SOURCE_H

class Source
{
public:
    Source(int id, double distance);

    int getId() { return this->id; }
    void setDistance(double distance) { this->distance = distance; }
    double getDistance() { return this->distance; }
    void setTotalRobots(int totalRobots) { this->totalRobots = totalRobots; }
    int getTotalRobots() { return this->totalRobots; }

private:
    int id;
    double distance;
    int totalRobots;
};

#endif // SOURCE_H

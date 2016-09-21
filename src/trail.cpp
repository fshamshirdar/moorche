#include <trail.h>

Trail::Trail() : cycle(0)
{
}

Trail::Point::Point(Stg::Pose pose, uint64_t createdCycle, double density = 1.0, int timesToTarget = 0, bool toSource = false) : pose(pose), createdCycle(createdCycle), timesToTarget(timesToTarget), toSource(toSource), density(density)
{
}

void Trail::Point::update(uint64_t cycle)
{
    this->density = 1.0 - (Config::EVAPORATION_COEFFICIENT_PER_CYCLE * (cycle - this->createdCycle));
}

void Trail::update(uint64_t cycle)
{
    this->cycle = cycle;
    std::vector<Trail::Point*>::iterator iterator;
    for (iterator = points.begin(); iterator != points.end();) {
        (*iterator)->update(cycle);
        if ((*iterator)->getDensity() <= 0) {
            delete (*iterator);
            iterator = points.erase(iterator);
        } else {
            iterator ++;
        }
    }
}

void Trail::addPoint(Stg::Pose pose) // Deprecated
{
    Trail::Point* point = new Trail::Point(pose, this->cycle);
    points.push_back(point);
}

void Trail::addPoints(std::vector<Stg::Pose> poses, bool toSource)
{
    int counter = 0;
    for (std::vector<Stg::Pose>::iterator it = poses.begin(); it != poses.end(); it++) {
        Trail::Point* point = new Trail::Point((*it), this->cycle, 1.0, poses.size() - counter, toSource);
        points.push_back(point);
        counter ++;
    }
}

Trail::Point* Trail::getClosestPoint(Stg::Pose pose)
{
    Trail::Point* closestPoint = NULL;
    double minDistance = 1000.0;
    std::vector<Trail::Point*>::iterator iterator;
    for (iterator = points.begin(); iterator != points.end(); iterator ++) {
        double distance = (*iterator)->getDistance(pose);
        if (distance <= minDistance) {
            closestPoint = (*iterator);
            minDistance = distance;
        }
    }

    return closestPoint;
}

Trail::Point* Trail::getAveragePointInCircle(Stg::Pose pose, double radius, bool toSource = false)
{
    double angle = 0.0;
    double density = 0.0;
    int count = 0;
    std::vector<Trail::Point*>::iterator iterator;
    for (iterator = points.begin(); iterator != points.end(); iterator ++) {
        if ((*iterator)->getDistance(pose) < radius && (*iterator)->isToSource() == toSource) {
            count ++;
            density += (*iterator)->getDensity();
            angle += (*iterator)->getPose().a;
        }
    }

    density /= count;
    angle /= count;

    Trail::Point* averagePoint = new Trail::Point(Stg::Pose(pose.x, pose.y, pose.z, angle), cycle, density);
    return averagePoint;
}

Trail::Point* Trail::getBestPointInCircle(Stg::Pose pose, double radius, bool toSource = false)
{
    Trail::Point* best = NULL;
    int bestScore = 1000;

    std::vector<Trail::Point*>::iterator iterator;
    for (iterator = points.begin(); iterator != points.end(); iterator ++) {
        if ((*iterator)->getDistance(pose) < radius && (*iterator)->isToSource() == toSource) {
            if ((*iterator)->getTimesToTarget() < bestScore) {
                best = (*iterator);
                bestScore = (*iterator)->getTimesToTarget();
            }
        }
    }

    return best;
}

void Trail::print()
{
    std::vector<Trail::Point*>::iterator iterator;
    for (iterator = points.begin(); iterator != points.end(); iterator ++) {
        std::cout<< "(" << (*iterator)->getPose().x << ", " << (*iterator)->getPose().y << ", " << (*iterator)->getPose().a << ")" << std::endl;
    }
    std::cout << "--------" << std::endl;
}

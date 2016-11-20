#include <trail.h>

Trail::Trail(Colony* colony) : colony(colony), cycle(0)
{
}

Trail::Point::Point(Stg::Pose pose, int foodId, uint64_t createdCycle, double density = 1.0, double distanceToTarget = 0.0, int timesToTarget = 0, int totalSteps = 0, bool toSource = false) : pose(pose), foodId(foodId), createdCycle(createdCycle), distanceToTarget(distanceToTarget), timesToTarget(timesToTarget), totalSteps(totalSteps), toSource(toSource), density(density)
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
            colony->getMap()->decreasePopulation((*iterator)->getPose());
            delete (*iterator);
            iterator = points.erase(iterator);
        } else {
            iterator ++;
        }
    }
}

void Trail::addPoints(std::vector<Stg::Pose> poses, int foodId, bool toSource)
{
    int counter = 0;
    double trailDistance = 0;
    Stg::Pose oldPoint;

    for (std::vector<Stg::Pose>::iterator it = poses.begin(); it != poses.end(); it++) {

        if (it != poses.begin()) {
            trailDistance += oldPoint.Distance(*it);
        }
        oldPoint = *it;

        Trail::Point* point = new Trail::Point((*it), foodId, this->cycle, 1.0, trailDistance, poses.size() - counter, poses.size(), toSource);
        // colony->getMap()->increasePopulation(point->getPose());
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

Trail::Point* Trail::getBestPointInCircle(Stg::Pose pose, int foodId, double radius, bool toSource = false)
{
    Trail::Point* best = NULL;
    double bestScore = 0;

    std::vector<Trail::Point*>::iterator iterator;
    for (iterator = points.begin(); iterator != points.end(); iterator ++) {
        if ((*iterator)->getFoodId() == foodId && (*iterator)->getDistance(pose) < radius && (*iterator)->isToSource() == toSource) {
            double density = colony->getMap()->getValue((*iterator)->getPose());
            double totalDensity = colony->getMap()->getTotalDensity();
            double maxDensity = colony->getMap()->getMaxDensity();
            double stepsToTarget = (*iterator)->getTimesToTarget();
            double totalSteps = (*iterator)->getTotalSteps();
            double score =
                    Config::STEPS_TO_TARGET_WEIGHT * (1. - (stepsToTarget / totalSteps)) -
                    Config::DENSITY_WEIGHT * (density / maxDensity);
            if (score > bestScore) {
                best = (*iterator);
                bestScore = score;
            }
        }
    }
    
/*
    double minCost = INFINITY;

    std::vector<Trail::Point*>::iterator iterator;
    for (iterator = points.begin(); iterator != points.end(); iterator ++) {
        if ((*iterator)->getDistance(pose) < radius && (*iterator)->isToSource() == toSource) {
            double density = colony->getMap()->getValue((*iterator)->getPose());
            double totalDensity = colony->getMap()->getTotalDensity();
            double maxDensity = colony->getMap()->getMaxDensity();
            double stepsToTarget = (*iterator)->getTimesToTarget();
            double totalSteps = (*iterator)->getTotalSteps();
            double cost =
                    Config::STEPS_TO_TARGET_WEIGHT * stepsToTarget +
                    Config::DENSITY_WEIGHT * (density / maxDensity);
            if (cost < minCost) {
                best = (*iterator);
                minCost = cost;
            }
        }
    }
    */
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

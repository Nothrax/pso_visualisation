#include <pso/function/LevyN13.h>

double LevyN13::calculateFitness(Point point) {
    return pow(sin(3 * _pi * point.x), 2) + (point.x - 1) * (point.x - 1) * (1 + pow(sin(3 * _pi * point.y), 2)) +
           (point.y - 1) * (point.y - 1) * (1 + pow(sin(2 * _pi * point.y), 2));
}

double LevyN13::getMinFitness() {
    return 0.0;
}

Point LevyN13::getBoundary() {
    Point point = {10.0, 10.0};
    return point;
}

std::string LevyN13::getMinPoint() {
    return "[1,1]";
}

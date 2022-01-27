#include <pso/function/Griewank.h>

double Griewank::calculateFitness(Point point) {
    return ((point.x * point.x) / 4000) + ((point.y * point.y) / 4000) -
           (cos(point.x / sqrt(1)) * cos(point.y / sqrt(2))) + 1;
}

double Griewank::getMinFitness() {
    return 0.0;
}

Point Griewank::getBoundary() {
    Point point = {100.0, 100.0};
    return point;
}

std::string Griewank::getMinPoint() {
    return "[0,0]";
}
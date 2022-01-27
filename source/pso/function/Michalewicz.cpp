#include <pso/function/Michalewicz.h>

double Michalewicz::calculateFitness(Point point) {
    return (sin(point.x) * pow(sin((1 * point.x * point.x) / _pi), 20)) +
           (sin(point.y) * pow(sin((2 * point.y * point.y) / _pi), 20));
}

double Michalewicz::getMinFitness() {
    return -1.8013;
}

Point Michalewicz::getBoundary() {
    Point point = {4.0, 4.0};
    return point;
}

std::string Michalewicz::getMinPoint() {
    return "[2.20,\n1.57]";
}
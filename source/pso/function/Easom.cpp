#include <pso/function/Easom.h>

double Easom::calculateFitness(Point point) {
    return -cos(point.x) * cos(point.y) *
           exp(-(point.x - _pi) * (point.x - _pi) - (point.y - _pi) * (point.y - _pi));
}

double Easom::getMinFitness() {
    return -1.0;
}

Point Easom::getBoundary() {
    Point point = {80.0, 80.0};
    return point;
}

std::string Easom::getMinPoint() {
    return "[3.14159,\n3.14159]";
}
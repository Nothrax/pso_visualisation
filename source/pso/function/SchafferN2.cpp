#include <pso/function/SchafferN2.h>

double SchafferN2::calculateFitness(Point point) {
    return 0.5 + (pow((sin(point.x * point.x - point.y * point.y) - 0.5), 2)) /
                 (pow((1 + 0.001 * (point.x * point.x + point.y * point.y)), 2));
}

double SchafferN2::getMinFitness() {
    return 0.0;
}

Point SchafferN2::getBoundary() {
    Point point = {10.0, 10.0};
    return point;
}

std::string SchafferN2::getMinPoint() {
    return "[0,0]";
}
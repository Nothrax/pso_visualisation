#include <pso/function/SchafferN4.h>

double SchafferN4::calculateFitness(Point point) {
    return 0.5 + (pow(cos(sin(fabs(point.x * point.x - point.y * point.y)) - 0.5), 2)) /
                 (pow((1 + 0.001 * (point.x * point.x + point.y * point.y)), 2));
}

double SchafferN4::getMinFitness() {
    return 0.292579;
}

Point SchafferN4::getBoundary() {
    Point point = {50.0, 50.0};
    return point;
}

std::string SchafferN4::getMinPoint() {
    return "[0,0]";
}
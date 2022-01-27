#include <pso/function/CrossInTray.h>

double CrossInTray::calculateFitness(Point point) {
    return -0.0001 * pow(fabs(sin(point.x) * sin(point.y) * exp(fabs(100 - (sqrt(point.x * point.x + point.y * point.y)) / M_PI))) + 1, 0.1);
}

Point CrossInTray::getBoundary() {
    Point point = {10.0, 10.0};
    return point;
}

double CrossInTray::getMinFitness() {
    return -2.06261;
}

std::string CrossInTray::getMinPoint() {
    return "[+-1.3491,\n+-1.3491]";
}
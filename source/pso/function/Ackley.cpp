#include <pso/function/Ackley.h>

double Ackley::calculateFitness(Point position) {
    return -20 * exp(-0.2 * sqrt(0.2 * (pow(position.x, 2) + pow(position.y, 2)))) -
           exp(0.5 * (cos(2 * M_PI * position.x) + cos(2 * M_PI * position.y))) + 20 + M_E;
}


double Ackley::getMinFitness() {
    return 0.0;
}

Point Ackley::getBoundary() {
    Point point = {40.0, 40.0};
    return point;
}

std::string Ackley::getMinPoint() {
    return "[0,0]";
}

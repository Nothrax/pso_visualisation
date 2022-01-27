#include <pso/function/Levy.h>

double Levy::calculateFitness(Point point) {
    double w1 = 1 + (point.x - 1) / 4;
    double w2 = 1 + (point.y - 1) / 4;
    return pow(sin(M_PI * w1), 2)
           + ((w1 - 1) * (w1 - 1) * (1 + 10 * pow(sin(M_PI * w1 + 1), 2)) +
              (w2 - 1) * (w2 - 1) * (1 + pow(sin(2 * M_PI * w2), 2)));
}

double Levy::getMinFitness() {
    return 0.0;
}

Point Levy::getBoundary() {
    Point point = {15.0, 15.0};
    return point;
}

std::string Levy::getMinPoint() {
    return "[1,1]";
}
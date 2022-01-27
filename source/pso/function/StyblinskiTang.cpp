#include <pso/function/StyblinskiTang.h>

double StyblinskiTang::calculateFitness(Point point) {
    return 0.5 * ((pow(point.x, 4) - 16 * point.x * point.x - 5 * point.x) +
                  (pow(point.y, 4) - 16 * point.y * point.y - 5 * point.y));
}

double StyblinskiTang::getMinFitness() {
    return -39.16599 * 2;
}

Point StyblinskiTang::getBoundary() {
    Point point = {5.0, 5.0};
    return point;
}

std::string StyblinskiTang::getMinPoint() {
    return "[-2.903534,\n-2.903534]";
}
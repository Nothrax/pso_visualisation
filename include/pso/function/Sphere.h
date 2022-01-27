#pragma once

#include <pso/function/Function.h>

///https://www.sfu.ca/~ssurjano/spheref.html
class Sphere : public Function {
public:
    double calculateFitness(Point point) override;

    std::string getMinPoint() override;

    double getMinFitness() override;

    Point getBoundary() override;
};
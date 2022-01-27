#pragma once

#include <pso/function/Function.h>

///https://www.sfu.ca/~ssurjano/ackley.html minimum is at 0,0
class Ackley final : public Function {
public:
    double calculateFitness(Point point) override;

    std::string getMinPoint() override;

    double getMinFitness() override;

    Point getBoundary() override;
};
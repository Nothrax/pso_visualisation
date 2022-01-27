#pragma once

#include <pso/function/Function.h>

///https://www.sfu.ca/~ssurjano/levy13.html
class LevyN13 : public Function {
public:
    double calculateFitness(Point point) override;

    std::string getMinPoint() override;

    double getMinFitness() override;

    Point getBoundary() override;
};
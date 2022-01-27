#pragma once

#include <pso/function/Function.h>

///https://www.sfu.ca/~ssurjano/schaffer4.html
class SchafferN4 : public Function {
public:
    double calculateFitness(Point point) override;

    std::string getMinPoint() override;

    double getMinFitness() override;

    Point getBoundary() override;
};
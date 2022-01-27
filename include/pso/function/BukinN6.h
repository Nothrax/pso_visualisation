#pragma once

#include <pso/function/Function.h>

///https://www.sfu.ca/~ssurjano/bukin6.html
class BukinN6 final : public Function {
public:
    double calculateFitness(Point point) override;

    std::string getMinPoint() override;

    double getMinFitness() override;

    Point getBoundary() override;
};
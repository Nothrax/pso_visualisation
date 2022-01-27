#pragma once

#include <pso/function/Function.h>

///https://www.sfu.ca/~ssurjano/crossit.html minimum is -2.06261
class CrossInTray final : public Function {
public:
    double calculateFitness(Point point) override;

    std::string getMinPoint() override;

    double getMinFitness() override;

    Point getBoundary() override;
};
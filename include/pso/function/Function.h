#pragma once

#include <pso/particle_swarm/Structures.h>

#include <string>
#include <cmath>

/**
 * Virtual class serving as interface for all function classes
 */
class Function {
public:
    /**
     * Calculating fitness function of point
     * @param point point to be calculated
     * @return fitness value
     */
    virtual double calculateFitness(Point point) = 0;

    /**
     * Get the best possible value (point in which function has a minimum)
     * @return point
     */
    virtual std::string getMinPoint() = 0;

    /**
     * Get minimum value that we are trying to find
     * @return
     */
    virtual double getMinFitness() = 0;

    /**
     * Get function boundary in which particle can move (one point, boundary is symetric)
     * @return boundary
     */
    virtual Point getBoundary();

protected:
};
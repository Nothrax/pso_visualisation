#pragma once

#include <memory>

class Function;

/**
 * Structure represents position
 */

struct Point{
    double x;
    double y;
};

/**
 * Structure with swarm options
 */
struct SwarmOptions{
    int numberOfSteps = 100; ///number of steps of simulation
    int numberOfParticles = 13; ///number of particles in simulation
    int numberOfNeighbours = 3; ///number of neighbours for single particle
    Point boundary = {40.0,40.0}; ///default function boundary
    double speedLimit = 1.0; ///default speed limit of particle
    double error = 0.0001; ///error for accepting fitness value
    std::shared_ptr<Function> function; ///function for optimalization
};
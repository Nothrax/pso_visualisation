#pragma once

#include <vector>
#include <cstdlib>
#include <random>
#include <iostream>
#include <cfloat>

#include <pso/particle_swarm/Structures.h>
#include <pso/function/Function.h>

/**
 * Class for simulating a particle
 */
class Particle {
public:
    /**
     * Constructor
     * @param boundary one point defining symmetric boundary in which particle can move
     * @param speedLimit maximum speed that particle can achieve
     * @param function function for optimizing
     */
    Particle(Point boundary, double speedLimit, const std::shared_ptr<Function> &function);

    /**
     * Destructor will clear particles neighbourhood
     */
    ~Particle();

    /**
     * Method will initialize a random position of particle within the function boundary, calculate its fitness,
     * check its neighbourhood and initialize its velocity
     */
    void initializeState();

    /**
     * Add particle to neighbourhood
     * @param particle particle to be added
     */
    void addNeighbour(const std::shared_ptr<Particle> &particle);

    /**
     * Make one step - calculate new position, fitness, velocity and check neighbourhood
     */
    void makeIteration();

    /**
     * Position getter
     * @return
     */
    Point getPosition();

    /**
     * Get best fitness in particle neighbourhood
     * @return fitness
     */
    double getBestNeighbourFitness();

    /**
     * Get best position in particle neighbourhood
     * @return position
     */
    Point getBestNeighbourPosition();

    /**
     * Setting best global result
     * @param globalFitness best global fitness
     * @param globalPoint  best global position
     */
    void setBestGlobalResult(double globalFitness, Point globalPoint);

    /**
     * Setting best local result
     * @param globalFitness best local fitness
     * @param globalPoint  best local position
     */
    void receiveBestNeighbourResult(Point position, double fitness);

    /**
     * Delete particles neighbourhood
     */
    void resetNeighbour();

private:
    Point position;
    Point velocity;
    double localFitness;
    double velocityLimit;
    Point boundary;
    std::shared_ptr<Function> function;
    const double w = 0.721;
    const double c = 1.193;
    const double c_g = 2.05;
    const double c_p = 2.05;
    Point g_i;

    Point bestGlobalPosition;
    Point bestNeighbourPosition;
    double bestGlobalFitness = DBL_MAX;
    double bestNeighbourFitness = DBL_MAX;
    std::vector<std::shared_ptr<Particle>> neighbourhood;

    void calculateFitness();

    void initializePosition();

    void initializeVelocity();

    void checkVelocity();

    void checkPosition();

    void tellFitnessToNeighbours();

    void calculateNewVelocity();

    void calculateNewPosition();

    void checkFitnessWithNeighbourhood();
};
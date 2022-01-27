#pragma once

#include <pso/particle_swarm/Particle.h>

/**
 * Swarm of particles for simulation
 */
class Swarm {
public:
    /**
     * Constructor
     * @param swarmOptions swarm options
     */
    explicit Swarm(SwarmOptions swarmOptions);

    /**
     * Destructor will reset particles
     */
    ~Swarm();

    /**
     * Method will create particles, set neighbourhood and initialize particles
     */
    void initializeSwarm();

    /**
     * Simulate swarm for all steps
     */
    void simulateSwarm();

    /**
     * Simulate one step
     * @return true if last step was simulated
     */
    bool makeStep();

    /**
     * Get best fitness
     * @return best fitness
     */
    double getBestFitness();

    /**
     * Get best position
     * @return best position
     */
    Point getBestPosition();

    /**
     * Get actual step number
     * @return actual step number
     */
    int getStepNumber();

    /**
     * Get vector of all particles position
     * @return vector of positions
     */
    std::vector<Point> getActualPositions();

private:
    std::vector<std::shared_ptr<Particle>> swarm;
    SwarmOptions swarmOptions;
    double bestFitness = DBL_MAX;
    Point bestPosition;
    double expectedResult;
    int stepNumber = 0;


    void createSwarm();

    void initializeParticles();

    void initializeNeighbourhoods();

    void broadcastGlobalResult();

    void compareParticleWithGlobalMinimum(const std::shared_ptr<Particle> &particle);
};
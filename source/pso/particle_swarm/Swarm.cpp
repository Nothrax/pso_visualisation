#include <pso/particle_swarm/Swarm.h>

Swarm::Swarm(SwarmOptions swarmOptions) {
    this->swarmOptions = swarmOptions;
}

void Swarm::initializeSwarm() {
    createSwarm();
    initializeNeighbourhoods();
    initializeParticles();

    expectedResult = swarmOptions.function->getMinFitness();
}

void Swarm::createSwarm() {
    for (int i = 0; i < swarmOptions.numberOfParticles; i++) {
        swarm.push_back(
                std::make_shared<Particle>(swarmOptions.boundary, swarmOptions.speedLimit, swarmOptions.function));
    }
}

void Swarm::initializeParticles() {
    for (auto const &particle: swarm) {
        particle->initializeState();
        compareParticleWithGlobalMinimum(particle);
    }
}

Point Swarm::getBestPosition() {
    return bestPosition;
}

double Swarm::getBestFitness() {
    return bestFitness;
}

void Swarm::initializeNeighbourhoods() {
    for (int i = 0; i < swarmOptions.numberOfParticles; i++) {
        int index = (i - 1);
        if (index < 0) {
            index = swarmOptions.numberOfParticles - 1;
        }
        swarm.at(i)->addNeighbour(swarm.at(index));
        swarm.at(i)->addNeighbour(swarm.at(i));
        index = (i + 1) % swarmOptions.numberOfParticles;
        swarm.at(i)->addNeighbour(swarm.at(index));
    }
}

void Swarm::broadcastGlobalResult() {
    for (auto const &particle: swarm) {
        particle->setBestGlobalResult(bestFitness, bestPosition);
    }
}

void Swarm::simulateSwarm() {
    bool end = false;
    while (!end) {
        end = makeStep();
    }
}

bool Swarm::makeStep() {
    for (auto const &particle: swarm) {
        particle->makeIteration();
        compareParticleWithGlobalMinimum(particle);
    }

    stepNumber++;

    if (fabs(expectedResult - bestFitness) < swarmOptions.error || stepNumber == swarmOptions.numberOfSteps) {
        return true;
    }
    return false;
}

void Swarm::compareParticleWithGlobalMinimum(const std::shared_ptr<Particle> &particle) {
    double particleFitness = particle->getBestNeighbourFitness();
    if (particleFitness < bestFitness) {
        bestFitness = particleFitness;
        bestPosition = particle->getBestNeighbourPosition();
        broadcastGlobalResult();
    }
}

std::vector<Point> Swarm::getActualPositions() {
    std::vector<Point> positions;
    for (auto const &particle: swarm) {
        positions.push_back(particle->getPosition());
    }
    return positions;
}

int Swarm::getStepNumber() {
    return stepNumber;
}

Swarm::~Swarm() {
    for (const auto &particle: swarm) {
        particle->resetNeighbour();
    }
    swarm.clear();
}

#include <pso/particle_swarm/Particle.h>

Particle::Particle(Point boundary, double speedLimit, const std::shared_ptr<Function> &function) {
    this->velocityLimit = speedLimit;
    this->boundary = boundary;
    this->function = function;
}

void Particle::initializeState() {
    initializePosition();
    calculateFitness();
    checkFitnessWithNeighbourhood();
    initializeVelocity();
    checkVelocity();
}


void Particle::initializePosition() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist_x(-boundary.x, boundary.x);
    std::uniform_real_distribution<double> dist_y(-boundary.y, boundary.y);
    //random position is taken inside of boundaries
    position.x = dist_x(mt);
    position.y = dist_y(mt);
}

void Particle::initializeVelocity() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist_x(-boundary.x - localFitness, boundary.x - localFitness);
    std::uniform_real_distribution<double> dist_y(-boundary.y - localFitness, boundary.y - localFitness);
    //SPSO 2006 velocity is calculated as v_i = U(min_d - x_(i,d)(0), max_d - x_(i,d)(0))/2
    velocity.x = dist_x(mt) / 2;
    velocity.y = dist_y(mt) / 2;
}

void Particle::checkVelocity() {
    if (fabs(velocity.x) > velocityLimit) {
        velocity.x = (velocity.x > 0) ? velocityLimit : -velocityLimit;
    }
    if (fabs(velocity.y) > velocityLimit) {
        velocity.y = (velocity.y > 0) ? velocityLimit : -velocityLimit;
    }
}

void Particle::calculateFitness() {
    localFitness = function->calculateFitness(position);
}

void Particle::tellFitnessToNeighbours() {
    for (auto const &particle: neighbourhood) {
        particle->receiveBestNeighbourResult(bestNeighbourPosition, bestNeighbourFitness);
    }
}

void Particle::receiveBestNeighbourResult(Point pos, double fitness) {
    if (fitness < bestNeighbourFitness) {
        bestNeighbourFitness = fitness;
        bestNeighbourPosition = pos;
    }
}

void Particle::addNeighbour(const std::shared_ptr<Particle> &particle) {
    neighbourhood.push_back(particle);
}

void Particle::setBestGlobalResult(double globalFitness, Point globalPoint) {
    this->bestGlobalFitness = globalFitness;
    this->bestGlobalPosition = globalPoint;
}

Point Particle::getBestNeighbourPosition() {
    return bestNeighbourPosition;
}

double Particle::getBestNeighbourFitness() {
    return bestNeighbourFitness;
}

void Particle::resetNeighbour() {
    neighbourhood.clear();
}

void Particle::makeIteration() {
    calculateNewVelocity();
    calculateNewPosition();
    calculateFitness();
    checkFitnessWithNeighbourhood();
}

void Particle::calculateNewVelocity() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, c);

    double r_p = dist(mt);
    double r_g = dist(mt);

    velocity.x =
            w * velocity.x + r_p * (bestGlobalPosition.x - position.x) + r_g * (bestNeighbourPosition.x - position.x);
    velocity.y =
            w * velocity.y + r_p * (bestGlobalPosition.y - position.y) + r_g * (bestNeighbourPosition.y - position.y);

    checkVelocity();
}

void Particle::calculateNewPosition() {
    position.x += velocity.x;
    position.y += velocity.y;

    checkPosition();

}

void Particle::checkPosition() {
    if (fabs(position.x) > boundary.x) {
        position.x = (position.x > 0) ? boundary.x : -boundary.x;
        velocity.x = 0;
    }
    if (fabs(position.y) > boundary.y) {
        position.y = (position.y > 0) ? boundary.y : -boundary.y;
        velocity.y = 0;
    }
}

void Particle::checkFitnessWithNeighbourhood() {
    if (localFitness < bestNeighbourFitness) {
        bestNeighbourFitness = localFitness;
        bestNeighbourPosition = position;
        tellFitnessToNeighbours();
    }
}

Point Particle::getPosition() {
    return position;
}

Particle::~Particle() {
    neighbourhood.clear();
}



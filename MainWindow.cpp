#include "MainWindow.h"

#include <pso/function/Ackley.h>
#include <pso/function/FunctionFactory.h>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    createSimulationButtons();
    createInputs();
    createPlot();
    createDropdowns();
}

void MainWindow::startAutoSimulation() {
    autoSimulationButton->setText("Simulation in progress");
    autoSimulationButton->setEnabled(false);
    this->repaint();
    updateSwarmOptions();
    swarm = std::make_shared<Swarm>(swarmOptions);

    swarm->initializeSwarm();
    swarm->simulateSwarm();

    updateStepResults();

    swarm.reset();
    repaintGraph();

    autoSimulationButton->setText("Start simulation");
    autoSimulationButton->setEnabled(true);
    this->repaint();
}

void MainWindow::handleNextStepButton() {
    autoSimulationButton->setText("Simulation in progress");
    autoSimulationButton->setEnabled(false);
    stepSimulationButton->setEnabled(false);
    this->repaint();

    bool end = swarm->makeStep();

    updateStepResults();
    repaintGraph();

    if (end) {
        recoverGuiFromStepSimulation();
        swarm.reset();
    } else {
        autoSimulationButton->setText("Finish simulation");
        autoSimulationButton->setEnabled(true);
        stepSimulationButton->setEnabled(true);
        this->repaint();
    }
}

void MainWindow::handleSimulationButton() {
    std::cout << "Starting simulation\nNumber of steps: " << swarmOptions.numberOfSteps
              << "\nNumber of particles:" << swarmOptions.numberOfParticles
              << "\nError: " << swarmOptions.error
              << "\nSpeed limit: " << swarmOptions.speedLimit << std::endl;

    if (autoSim) {
        startAutoSimulation();
    } else {
        if (inSimulation) {
            while (!swarm->makeStep());
            updateStepResults();
            repaintGraph();
            recoverGuiFromStepSimulation();
            swarm.reset();

        } else {
            setGuiForStepSimulation();
            updateSwarmOptions();
            swarm = std::make_shared<Swarm>(swarmOptions);
            swarm->initializeSwarm();
            handleNextStepButton();
        }
    }

}

void MainWindow::createPlot() {
    customPlot = new QCustomPlot(this);
    //customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    customPlot->setGeometry(0, 0, 650, 600);
    customPlot->axisRect()->setupFullAxesBox(true);
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");


    colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
    colorScale = new QCPColorScale(customPlot);
    customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(
            QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale


    auto marginGroup = new QCPMarginGroup(customPlot);
    customPlot->axisRect()->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom | QCP::msTop, marginGroup);
    colorMap->setGradient(QCPColorGradient::gpPolar);

    //customPlot->addGraph();

    dwPoints = new QCPGraph(customPlot->xAxis, customPlot->yAxis);
    dwPoints->setAdaptiveSampling(false);
    dwPoints->setLineStyle(QCPGraph::lsNone);
    dwPoints->setScatterStyle(QCPScatterStyle::ssPlusCircle);
    dwPoints->setPen(QPen(QBrush(Qt::white), 1));
}

void MainWindow::handleFunctionChange(const QString &command_text) {
    std::cout << "Function changed: " << command_text.toStdString() << std::endl;
    swarmOptions.function = FunctionFactory::makeFunction(command_text.toStdString());
    if(swarmOptions.function == nullptr){
        swarmOptions.function = std::make_shared<Ackley>();
        functionSelector->setCurrentIndex(0);
    }

    if (swarmOptions.function != nullptr) {
        clearStepResults();
        std::string labelString = command_text.toStdString() + std::string(" function");
        std::string globalMinimaString =
                "Global minima:\n" + std::to_string(swarmOptions.function->getMinFitness()) + " at\n" +
                swarmOptions.function->getMinPoint();
        globalMinimaLabel->setText(globalMinimaString.c_str());
        colorScale->axis()->setLabel(labelString.c_str());
        particleLocation.clear();
        fillFunctionArray();
        repaintGraph();
    }
}

void MainWindow::fillFunctionArray() {

    for (int i = 0; i < graphResolutionX; i++) {
        delete functionArray[i];
    }
    delete functionArray;

    swarmOptions.boundary = swarmOptions.function->getBoundary();
    graphResolutionX = swarmOptions.boundary.x * 20;
    graphResolutionY = swarmOptions.boundary.y * 20;
    functionArray = new double *[graphResolutionX];
    for (int i = 0; i < graphResolutionX; i++) {
        functionArray[i] = new double[graphResolutionY];
    }

    std::cout << "Calculating new fitness" << std::endl;
    Point point;
    for (int x = 0; x < graphResolutionX; x++) {
        for (int y = 0; y < graphResolutionY; y++) {
            point.x = ((double) x - graphResolutionX / 2) / 10;
            point.y = ((double) y - graphResolutionY / 2) / 10;
            functionArray[x][y] = swarmOptions.function->calculateFitness(point);
        }
    }

}

void MainWindow::repaintGraph() {
    colorMap->data()->setSize(graphResolutionX,
                              graphResolutionY); // we want the color map to have graphResolutionX * graphResolutionY data points
    colorMap->data()->setRange(QCPRange(-swarmOptions.boundary.x, swarmOptions.boundary.x),
                               QCPRange(-swarmOptions.boundary.y,
                                        swarmOptions.boundary.y)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions

    double x, y;
    for (int xIndex = 0; xIndex < graphResolutionX; xIndex++) {
        for (int yIndex = 0; yIndex < graphResolutionY; yIndex++) {
            colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
            colorMap->data()->setCell(xIndex, yIndex, functionArray[xIndex][yIndex]);
        }
    }
    colorMap->rescaleDataRange();
    colorScale->rescaleDataRange(true);

    QVector<double> step_value_x;
    QVector<double> step_value_y;
    for (Point &point: particleLocation) {
        step_value_x.push_back(point.x);
        step_value_y.push_back(point.y);
    }
    dwPoints->setData(step_value_x, step_value_y);

    customPlot->rescaleAxes();
    customPlot->replot();
}


void MainWindow::createSimulationButtons() {
    autoSimulationButton = new QPushButton("Start simulation", this);
    autoSimulationButton->setGeometry(QRect(QPoint(650, 550),
                                            QSize(150, 50)));
    connect(autoSimulationButton, SIGNAL (released()), this, SLOT (handleSimulationButton()));


    stepSimulationButton = new QPushButton("Next Step", this);
    stepSimulationButton->setGeometry(QRect(QPoint(650, 500),
                                            QSize(150, 50)));
    connect(stepSimulationButton, SIGNAL (released()), this, SLOT (handleNextStepButton()));
    stepSimulationButton->setDisabled(true);
}

void MainWindow::createInputs() {
    numberOfStepsLabel = new QLabel("Number of steps", this);
    numberOfStepsLabel->setGeometry(650, 0, 150, 25);
    numberOfStepsLabel->setAlignment(Qt::AlignCenter);

    numberOfStepsInput = new QSpinBox(this);
    numberOfStepsInput->setMinimum(1);
    numberOfStepsInput->setMaximum(1000000);
    numberOfStepsInput->setGeometry(650, 25, 150, 25);
    numberOfStepsInput->setValue(swarmOptions.numberOfSteps);
    numberOfStepsInput->setAlignment(Qt::AlignCenter);


    numberOfParticlesLabel = new QLabel("Number of particles", this);
    numberOfParticlesLabel->setGeometry(650, 100, 150, 25);
    numberOfParticlesLabel->setAlignment(Qt::AlignCenter);

    numberOfParticlesInput = new QSpinBox(this);
    numberOfParticlesInput->setMinimum(1);
    numberOfParticlesInput->setMaximum(1000);
    numberOfParticlesInput->setGeometry(650, 125, 150, 25);
    numberOfParticlesInput->setValue(swarmOptions.numberOfParticles);
    numberOfParticlesInput->setAlignment(Qt::AlignCenter);


    speedLimitLabel = new QLabel("Speed limit", this);
    speedLimitLabel->setGeometry(650, 150, 150, 25);
    speedLimitLabel->setAlignment(Qt::AlignCenter);

    speedLimitInput = new QDoubleSpinBox(this);
    speedLimitInput->setMinimum(0.0);
    speedLimitInput->setDecimals(5);
    speedLimitInput->setMaximum(100.0);
    speedLimitInput->setSingleStep(0.1);
    speedLimitInput->setGeometry(650, 175, 150, 25);
    speedLimitInput->setValue(swarmOptions.speedLimit);
    speedLimitInput->setAlignment(Qt::AlignCenter);

    errorLabel = new QLabel("Error", this);
    errorLabel->setGeometry(650, 200, 150, 25);
    errorLabel->setAlignment(Qt::AlignCenter);

    errorInput = new QDoubleSpinBox(this);
    errorInput->setDecimals(10);
    errorInput->setMinimum(0.0);
    errorInput->setMaximum(100.0);
    errorInput->setSingleStep(0.01);
    errorInput->setGeometry(650, 225, 150, 25);
    errorInput->setValue(swarmOptions.error);
    errorInput->setAlignment(Qt::AlignCenter);

    colorMapLabel = new QLabel("Grayscale: ", this);
    colorMapLabel->setGeometry(650, 250, 100, 25);
    colorMapLabel->setAlignment(Qt::AlignCenter);

    colorMapCheckbox = new QCheckBox(this);
    colorMapCheckbox->setGeometry(750, 250, 100, 25);
    connect(colorMapCheckbox, SIGNAL(toggled(bool)), this, SLOT(handleColorMapToggle(bool)));

    stepCheckboxLabel = new QLabel("Auto-sim: ", this);
    stepCheckboxLabel->setGeometry(650, 275, 100, 25);
    stepCheckboxLabel->setAlignment(Qt::AlignCenter);

    stepCheckbox = new QCheckBox(this);
    stepCheckbox->setGeometry(750, 275, 100, 25);
    stepCheckbox->setChecked(true);
    connect(stepCheckbox, SIGNAL(toggled(bool)), this, SLOT(handleStepToggle(bool)));

    globalMinimaLabel = new QLabel("Global minima:\n-", this);
    globalMinimaLabel->setGeometry(650, 300, 150, 75);
    globalMinimaLabel->setAlignment(Qt::AlignCenter);


    stepLabel = new QLabel("Step number: -", this);
    stepLabel->setGeometry(650, 375, 150, 25);
    stepLabel->setAlignment(Qt::AlignCenter);

    bestPositionLabel = new QLabel("Best position found:\n[-.-,\n-.-]", this);
    bestPositionLabel->setGeometry(650, 400, 150, 60);
    bestPositionLabel->setAlignment(Qt::AlignCenter);

    bestFitnessLabel = new QLabel("Best fitness found:\n-", this);
    bestFitnessLabel->setGeometry(650, 460, 150, 40);
    bestFitnessLabel->setAlignment(Qt::AlignCenter);


}

void MainWindow::createDropdowns() {
    functionSelectorLabel = new QLabel("Select function", this);
    functionSelectorLabel->setGeometry(650, 50, 150, 25);
    functionSelectorLabel->setAlignment(Qt::AlignCenter);

    functionSelector = new QComboBox(this);
    functionSelector->setGeometry(650, 75, 150, 25);
    functionSelector->addItems(functions);
    connect(functionSelector, &QComboBox::currentTextChanged, this, &MainWindow::handleFunctionChange);
    handleFunctionChange(functionSelector->currentText());
}

void MainWindow::handleColorMapToggle(bool state) {
    if (state) {
        colorMap->setGradient(QCPColorGradient::gpGrayscale);
        dwPoints->setPen(QPen(QBrush(Qt::red), 1));
    } else {
        colorMap->setGradient(QCPColorGradient::gpPolar);
        dwPoints->setPen(QPen(QBrush(Qt::white), 1));
    }
    customPlot->replot();
}

void MainWindow::handleStepToggle(bool state) {
    autoSim = state;
}

void MainWindow::updateSwarmOptions() {
    swarmOptions.numberOfSteps = numberOfStepsInput->value();
    swarmOptions.numberOfParticles = numberOfParticlesInput->value();
    swarmOptions.numberOfNeighbours = 3;
    swarmOptions.speedLimit = speedLimitInput->value();
    swarmOptions.error = errorInput->value();
}


void MainWindow::recoverGuiFromStepSimulation() {
    inSimulation = false;

    stepCheckbox->setDisabled(false);
    autoSimulationButton->setText("Start simulation");
    autoSimulationButton->setDisabled(false);
    stepSimulationButton->setDisabled(true);

    stepCheckbox->setDisabled(false);
    numberOfStepsInput->setDisabled(false);
    numberOfParticlesInput->setDisabled(false);
    errorInput->setDisabled(false);
    speedLimitInput->setDisabled(false);
    functionSelector->setDisabled(false);
    this->repaint();
}

void MainWindow::setGuiForStepSimulation() {
    inSimulation = true;

    autoSimulationButton->setText("Finish simulation");
    stepSimulationButton->setDisabled(false);

    stepCheckbox->setDisabled(true);
    numberOfStepsInput->setDisabled(true);
    numberOfParticlesInput->setDisabled(true);
    errorInput->setDisabled(true);
    speedLimitInput->setDisabled(true);
    functionSelector->setDisabled(true);
    this->repaint();
}

void MainWindow::updateStepResults() {
    double resultFitness = swarm->getBestFitness();
    Point resultPosition = swarm->getBestPosition();
    particleLocation = swarm->getActualPositions();
    stepNumber = swarm->getStepNumber();

    std::string bestFitnessText = "Best fitness found:\n" + std::to_string(resultFitness);
    std::string bestPositionText =
            "Best position found:\n[" + std::to_string(resultPosition.x) + ",\n" + std::to_string(resultPosition.y) +
            "]";
    std::string stepNumberText = "Step number: " + std::to_string(stepNumber);
    bestPositionLabel->setText(bestPositionText.c_str());
    bestFitnessLabel->setText(bestFitnessText.c_str());
    stepLabel->setText(stepNumberText.c_str());
}

void MainWindow::clearStepResults() {
    bestPositionLabel->setText("Best position found:\n[-.-,\n-.-]");
    bestFitnessLabel->setText("Best fitness found:\n-");
    stepLabel->setText("Step number: -");
}

MainWindow::~MainWindow() {
    for (int i = 0; i < graphResolutionX; i++) {
        delete[]functionArray[i];
    }
    delete[]functionArray;
    swarm.reset();
}






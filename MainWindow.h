#pragma once

#include <pso/particle_swarm/Swarm.h>

#include <qcustomplot/qcustomplot.h>

#include <QCoreApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QCheckBox>

#include <vector>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

    /**
     * Handler for simulation button
     */

    void handleSimulationButton();

    /**
     * Handler for next step button
     */
    void handleNextStepButton();

    /**
     * Handler for function change button
     */
    void handleFunctionChange(const QString &command_text);

    /**
     * Handler for color map toggle
     */
    void handleColorMapToggle(bool state);

    /**
     * Handler for step toggle
     */
    void handleStepToggle(bool state);

private:
    QPushButton *autoSimulationButton = nullptr;
    QPushButton *stepSimulationButton = nullptr;

    QCustomPlot *customPlot = nullptr;

    QSpinBox *numberOfStepsInput = nullptr;
    QLabel *numberOfStepsLabel = nullptr;

    QSpinBox *numberOfParticlesInput = nullptr;
    QLabel *numberOfParticlesLabel = nullptr;

    QDoubleSpinBox *errorInput = nullptr;
    QLabel *errorLabel = nullptr;

    QDoubleSpinBox *speedLimitInput = nullptr;
    QLabel *speedLimitLabel = nullptr;

    QLabel *bestPositionLabel = nullptr;
    QLabel *bestFitnessLabel = nullptr;
    QLabel *stepLabel = nullptr;

    QCheckBox *colorMapCheckbox = nullptr;
    QLabel *colorMapLabel = nullptr;

    QCheckBox *stepCheckbox = nullptr;
    QLabel *stepCheckboxLabel = nullptr;


    QCPColorMap *colorMap = nullptr;
    QCPColorScale *colorScale = nullptr;

    QLabel *functionSelectorLabel;
    QComboBox *functionSelector;

    QCPGraph *dwPoints = nullptr;
    QLabel *globalMinimaLabel = nullptr;

    bool autoSim = true;
    bool inSimulation = false;

    QStringList functions = {"Ackley", "Cross-in-tray", "Griewank", "Sphere", "Six-Hump Camel", "Easom", "Michalewicz",
                             "Styblinski-Tang", "Bukin N.6", "Drop-Wave", "Holder Table", "Schaffer N.4",
                             "Schaffer N.2",
                             "Levy", "Levy N.13"};
    std::vector<Point> particleLocation;
    unsigned int graphResolutionX = 0;
    unsigned int graphResolutionY = 0;
    double **functionArray = nullptr;

    SwarmOptions swarmOptions;
    std::shared_ptr<Swarm> swarm;
    int stepNumber = 0;

    void createSimulationButtons();

    void createInputs();

    void createDropdowns();

    void createPlot();

    void startAutoSimulation();

    void fillFunctionArray();

    void repaintGraph();

    void updateSwarmOptions();

    void setGuiForStepSimulation();

    void recoverGuiFromStepSimulation();

    void updateStepResults();

    void clearStepResults();
};
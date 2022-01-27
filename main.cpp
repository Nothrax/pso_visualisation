#include <QApplication>

#include "MainWindow.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.setFixedSize(800,600);
    mainWindow.show();

    return QApplication::exec();
}

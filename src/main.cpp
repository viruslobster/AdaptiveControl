#include <QtGui/QApplication>
#include "mainwindow.h"
#include <ctime> 
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include "Math.h"
#include "NeuralNetwork.h"

using namespace std;

int main(int argc, char** argv) {
    srand((unsigned)time(0));
    QApplication app(argc, argv);
    MainWindow foo;
    foo.show();
    return app.exec();   
}

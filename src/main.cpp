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
    //QApplication app(argc, argv);
    //MainWindow foo;
    //foo.show();
    //return app.exec();
    NeuralNetwork nn(1,1,3,3);
    nn.print();
    /*
    for(int i=0;i<600;i	++) {
      double f = (double)rand() / RAND_MAX;
      double num = f * (100);
      vector<double> input;
      input.push_back(num);
      double out = nn.input(input)[0];
      cout << "IN: " << num << ", OUT: " << out * 100<< endl;
      nn.learn(num - out * 100);
    }
    */
    
    vector<double> input;
    input.push_back(10);
    cout << nn.input(input)[0] << endl;
    return 0;
}

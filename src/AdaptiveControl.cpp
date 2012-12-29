#include "AdaptiveControl.h"

#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QAction>
#include <iostream>
#include "Math.h"


using namespace std;

AdaptiveControl::AdaptiveControl() {
  updater = new QTimer(this);  
  connect(updater, SIGNAL(timeout()), this, SLOT(updateLoop()));
  updater->start(100);
}

AdaptiveControl::~AdaptiveControl(){
  
  
}

double AdaptiveControl::f(double x) {
  return 0;
}

double AdaptiveControl::g(double x) {
  return sin(x);  
}

double AdaptiveControl::h(double x) {
  if(x < 6 * PI) return 0;
  if(x >= 6 * PI) return sin(x);
}



void AdaptiveControl::updateLoop() {
  cout << "hello" << endl;
}




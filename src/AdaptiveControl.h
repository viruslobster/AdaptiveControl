#ifndef AdaptiveControl_H
#define AdaptiveControl_H

#include <QtGui/QMainWindow>
#include <QTimer>
#include "Controller.h"
#include "Robot.h"

class AdaptiveControl : public QMainWindow {
Q_OBJECT
public:
  AdaptiveControl();
  virtual ~AdaptiveControl();
private slots:
  void updateLoop();
private:
  double f(double x);
  double g(double x);
  double h(double x);
  QTimer* updater;
  Controller* controller;
  Robot* robot;
  double (*pathFunction)(double);
  double speed;
  
};

#endif // AdaptiveControl_H

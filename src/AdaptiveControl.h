#ifndef AdaptiveControl_H
#define AdaptiveControl_H

#include <QtGui/QMainWindow>
#include <QTimer>

class AdaptiveControl : public QMainWindow
{
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
};

#endif // AdaptiveControl_H
